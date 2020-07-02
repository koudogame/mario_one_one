#include "play.hpp"
#include "scene_manager.hpp"

PlayScene::PlayScene()
{
    // �N���X�|�C���^������
    item_    = nullptr;
    enemy_   = nullptr;
    field_   = nullptr;
    player_  = nullptr;
    pos_col_ = nullptr;
    block_ = nullptr;
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
    pos_col_ = new PosCollision();
    block_ = new BreakBlock();

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
    player_->initialize();
    block_->initialize();

    touch_ = 0;
 
    return true;
}

void PlayScene::update()
{
    player_->update();

    field_->downBlock();

    field_->update( player_->getBreakRightX(), player_->getBreakRightY(),
        player_->getBreakLeftX(), player_->getBreakLeftY(), player_->getStatus() );

    item_->update( player_->getBreakRightX(), player_->getBreakRightY(),
        player_->getBreakLeftX(), player_->getBreakLeftY(), player_->getStatus(), player_->getScrollCnt() );

    enemy_->update( player_->getScrollCnt() );

    block_->update(player_->getBreakRightX(), player_->getBreakRightY(),
        player_->getBreakLeftX(), player_->getBreakLeftY());

    // get�֐����Ă�Ő��l��n���iItem�j
    for( int i = 0; i < item_->getHeight(); i++ )
    {
        for( int j = 0; j < item_->getWidth(); j++ )
        {
            if( pos_col_->getCollision( player_->getPositionX(), player_->getPositionY(),
                item_->getItemPosX( i, j ), item_->getItemPosY( i, j ) ) == false )
            {
                int id = item_->getId( i, j );

                // �����蔻�����肽��Id�����Փ˂��m���߂�
                if( id == kPowerup || id == kPowerup2 )
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
            if( pos_col_->getEnemyCollision(
                player_->getPositionX(), player_->getPositionY(),
                enemy_->getEnemyPosX( i, j ), enemy_->getEnemyPosY( i, j ),
                player_->getStatus() ) == 1 )
            {
                int id = enemy_->getId( i, j );
                touch_ = 1;

                // �ォ�瓥�݂����Ƃ�
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

    //// �N���A������Scene�؂�ւ�
    //if( !player_->getEnd() )
    //    SceneManager::ChangeScene( SceneManager::Scene::Result );
}

void PlayScene::draw()
{       
    field_->drawFront(player_->getScrollCnt());  
    block_->draw(player_->getScrollCnt());
    item_->draw(player_->getScrollCnt());
    field_->draw( player_->getScrollCnt() );
    enemy_->draw(player_->getScrollCnt());
    player_->draw();
}

void PlayScene::finalize()
{
    // DeleteGraph�Ȃ�
    field_->finalize();
    block_->finalize();
    item_->finalize();
    enemy_->finalize();
    player_->finalize();

    // �������J��new������]
    delete item_;
    delete block_;
    delete field_;
    delete player_;
    delete pos_col_;
}