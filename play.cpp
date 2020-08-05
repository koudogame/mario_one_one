#include "play.hpp"
#include "scene_manager.hpp"

PlayScene::PlayScene()
{
    // �N���X�|�C���^������
    gf_      = nullptr;
    ui_      = nullptr;
    bm_      = nullptr;
    item_    = nullptr;
    enemy_   = nullptr;
    field_   = nullptr;
    player_  = nullptr;
    pos_col_ = nullptr;
}

PlayScene::~PlayScene()
{
}

bool PlayScene::initialize()
{
    // �C���X�^���X�̐���
    field_   = new Field();   
    item_    = new Item( field_ );
    enemy_   = new Enemy( field_ );
    player_  = new Player( field_ );
    bm_      = new BallManagement( field_ );
    pos_col_ = new PosCollision(); 
    ui_      = new UIManager();
    gf_      = new GoalFire();

    // �t�@�C���ɑ΂�����̓X�g���[��
    std::fstream stage;
    std::fstream item;
    std::fstream enemy;

    // ���͂̂��߂ɃI�[�v��������o�͂��o�C�i���ōs��
    stage.open( "mario_field2.fmf", std::ios_base::in | std::ios_base::binary );
    enemy.open( "mario_enemy.fmf", std::ios_base::in | std::ios_base::binary );
    item.open( "mario_item.fmf", std::ios_base::in | std::ios_base::binary );

    // �N���X���̏��������s��
    item_->initialize( item );
    enemy_->initalize( enemy );
    field_->initialize( stage );
    bm_->initialize();
    player_->initialize();
    ui_->initialize();
    gf_->initialize();

    gf_flag_ = true;
    touch_ = 0;
    clear_num_ = 0;
    change_timer_ = 0;
 
    return true;
}

void PlayScene::update()
{
    player_->update( ui_->timeLimit() );

    // �}���I�������g�k�� �����~�߂邂d
    if( player_->getInvincibleTime() )
    {
        field_->downBlock();

        field_->update( player_->getBreakRightX(), player_->getBreakRightY(),
            player_->getBreakLeftX(), player_->getBreakLeftY(), player_->getStatus() );

        item_->update( player_->getBreakRightX(), player_->getBreakRightY(),
            player_->getBreakLeftX(), player_->getBreakLeftY(), player_->getStatus(), player_->getScrollCnt() );

        item_->getGoal( player_->getGoal() );

        enemy_->update( player_->getScrollCnt() );

        bm_->update( player_->getPositionX(), player_->getPositionY(),
            player_->getStatus(), player_->getDirection(), player_->getGoal(), player_->getPosY(), player_->getPushSquat() );

        ui_->coinCheck( item_->getCoin() );

        ui_->update( player_->getGoal() );

        bm_->posCheck( player_->getScrollCnt() );           // �d���Ȃ�Ȃ��悤�ɉ�ʊO�͔��肵�Ȃ�����
        bm_->sideCheck();                                   // �����瓖�����������

        // �Q�[���I�[�o�[�ł͂Ȃ��Ƃ�
        if( player_->getGameover() )
        {
            // �G�ƓG�̓����蔻������
            for( int i = 0; i < enemy_->getHeight(); i++ )
            {
                for( int j = 0; j < enemy_->getWidth(); j++ )
                {
                    // �N���{�[�A�m�R�m�R�ȊO�̂Ƃ��X�L�b�v
                    if( enemy_->getId( i, j ) != kKuribo && enemy_->getId( i, j ) != kTurtle )
                        continue;


                    for( int k = 0; k < enemy_->getHeight(); k++ )
                    {
                        for( int l = 0; l < enemy_->getWidth(); l++ )
                        {
                            // �N���{�[�A�m�R�m�R�ȊO�̂Ƃ��X�L�b�v
                            if( enemy_->getId( k, l ) != kKuribo && enemy_->getId( k, l ) != kTurtle )
                                continue;

                            // �������l�̎��͔��肵�Ȃ�
                            if( i == k && j == l )
                                continue;


                            // �GA�ƓGB�̔�������
                            if( pos_col_->getCollision(
                                enemy_->getEnemyPosX( i, j ), enemy_->getEnemyPosY( i, j ),
                                enemy_->getEnemyPosX( k, l ), enemy_->getEnemyPosY( k, l ) ) == false )
                            {
                                // �Փ˂��Ă���Ƃ�
                                // ���ꂼ��𔽑Ε����ɕ��܂���
                                enemy_->changeDirection( i, j );
                            }
                        }
                    }
                }
            }

            // get�֐����Ă�Ō��ʂ�Ԃ�(enemy & enemy)
            for( int i = 0; i < enemy_->getHeight(); i++ )
            {
                for( int j = 0; j < enemy_->getWidth(); j++ )
                {
                    for( int k = 0; k < bm_->getSize(); k++ )
                    {
                        // ���ׂẲ��ƓG�̏Փ˂��m�F
                        if( pos_col_->getFireEnemyCollision( bm_->getFirePosX( k ), bm_->getFirePosY( k ),
                            enemy_->getEnemyPosX( i, j ), enemy_->getEnemyPosY( i, j ) ) == false )
                        {
                            // ���A�G�p�ɐV���Ȋ֐���p�ӂ���
                            bm_->enemyCollision( k );
                            enemy_->fireCollision( i, j );
                        }
                    }
                }
            }

            // get�֐����Ă�Ő��l��n���iItem�j
            for( int i = 0; i < item_->getHeight(); i++ )
            {
                for( int j = 0; j < item_->getWidth(); j++ )
                {
                    // �A�C�e���ƃ}���I�̏Փ˔���𒲂ׂ�
                    if( pos_col_->getCollision( player_->getPositionX(), player_->getPositionY(),
                        item_->getItemPosX( i, j ), item_->getItemPosY( i, j ) ) == false )
                    {
                        int id = item_->getId( i, j );

                        // �����蔻�����肽��Id�����Փ˂��m���߂�
                        if( id == kMashroom || id == kFlower )
                        {
                            player_->itemCollision();
                            item_->posCollision( i, j );
                        }
                    }
                }
            }

            // get�֐����Ă�Ő��l��n���iEnemy�j
            for( int i = 0; i < enemy_->getHeight(); i++ )
            {
                for( int j = 0; j < enemy_->getWidth(); j++ )
                {
                    // �ォ�瓥�݂����Ƃ�
                    if( pos_col_->getEnemyCollision(
                        player_->getPositionX(), player_->getPositionY(),
                        enemy_->getEnemyPosX( i, j ), enemy_->getEnemyPosY( i, j ),
                        player_->getStatus() ) == 1 )
                    {
                        int id = enemy_->getId( i, j );
                        touch_ = 1;

                        if( id == kKuribo || id == kTurtle )
                        {
                            // ���܂ꂽ��̉��o
                            player_->enemyStepon();
                            enemy_->posCollision( i, j, touch_ );
                        }

                        // �ォ��b�����݂����Ƃ�
                        if( id == kShell )
                        {
                            // ���܂ꂽ��̉��o
                            player_->enemyStepon();
                            enemy_->shellCollision( i, j );
                        }
                    }
                    // �̂̉E�ƏՓ˂����Ƃ�
                    else if( pos_col_->getEnemyCollision(
                        player_->getPositionX(), player_->getPositionY(),
                        enemy_->getEnemyPosX( i, j ), enemy_->getEnemyPosY( i, j ),
                        player_->getStatus() ) == 2 )
                    {
                        int id = enemy_->getId( i, j );
                        touch_ = 2;

                        if( id == kShell )
                        {
                            // �b���������Ă��邩
                            if( enemy_->getPushFlag( i, j ) )
                                enemy_->posCollision( i, j, touch_ );
                            else
                            {
                                // ���G���Ԓ��͓����蔻������Ȃ�
                                if( player_->getInvincible() )
                                    player_->enemyCollision();
                            }
                        }

                        if( id == kKuribo || id == kTurtle )
                        {
                            // ���G���Ԓ��͓����蔻������Ȃ�
                            if( player_->getInvincible() == true )
                                player_->enemyCollision();
                        }

                    }
                    // �̂̍��ƏՓ˂����Ƃ�
                    else if( pos_col_->getEnemyCollision(
                        player_->getPositionX(),
                        player_->getPositionY(),
                        enemy_->getEnemyPosX( i, j ),
                        enemy_->getEnemyPosY( i, j ),
                        player_->getStatus() ) == 3 )
                    {
                        int id = enemy_->getId( i, j );
                        touch_ = 3;

                        if( id == kShell )
                        {
                            // �b���������Ă��邩
                            if( enemy_->getPushFlag( i, j ) )
                                enemy_->posCollision( i, j, touch_ );
                            else
                            {
                                // ���G���Ԓ��͓����蔻������Ȃ�
                                if( player_->getInvincible() )
                                    player_->enemyCollision();
                            }
                        }

                        if( id == kKuribo || id == kTurtle )
                        {
                            // ���G���Ԓ��͓����蔻������Ȃ�
                            if( player_->getInvincible() )
                                player_->enemyCollision();
                        }
                    }
                }
            }

            // �������O(�ꌅ���擾)
            if( player_->getEnd() )
            {
                clear_num_ = ui_->getTime() % 10;
                gf_flag_ = gf_->numCheck( clear_num_ );
            }
            // ��������
            else
            {
                // 0�ɂȂ�܂ŃX�R�A���Z
                if( ui_->getTime() != 0 )
                    // UI���Ŋ֐����܂킷
                    ui_->timeScore(); 
                else
                {
                    // �X�R�A���Z��Ɋ����f����
                    item_->getEnd( player_->getEnd() );

                    // �P����1,3,6�̎�
                    if( !gf_flag_ )
                    {

                        // numCheck��0�ȊO�̎�
                        if( gf_->getNumber() != 0 )
                            gf_->createFire();

                        if( !gf_->getSceneFlag() )
                            resultScene();
                    }
                    else
                        resultScene();
                }
            }
        }
        else
            // �Q�[���I�[�o�[���b��V�[���`�F���W
            resultScene();
    }
}

void PlayScene::draw()
{       
    field_->drawFront(player_->getScrollCnt());     // �t�B�[���h�w�i
    item_->draw(player_->getScrollCnt());           // �A�C�e��
    field_->draw( player_->getScrollCnt() );        // �G���u���b�N
    enemy_->draw(player_->getScrollCnt());          // �G
    bm_->draw( player_->getScrollCnt() );           // �t�@�C�A�{�[��
    player_->draw();                                // �}���I
    ui_->draw();                                    // UI
    gf_->draw();                                    // �ԉ�
}

void PlayScene::finalize()
{
    // DeleteGraph�Ȃ�
    field_->finalize();
    item_->finalize();
    enemy_->finalize();
    bm_->finalize();
    player_->finalize();
    ui_->finalize();
    gf_->finalize();

    // �������J��new������
    delete gf_;
    delete ui_;
    delete bm_;
    delete item_;
    delete field_;
    delete enemy_;
    delete player_;
    delete pos_col_;
}

void PlayScene::resultScene()
{
    change_timer_++;

    if( change_timer_ > kChangeTime )
        SceneManager::ChangeScene( SceneManager::Scene::Result );
}