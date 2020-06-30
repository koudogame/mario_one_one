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

    // �t�@�C���ɑ΂�����̓X�g���[��
    std::fstream stage;
    std::fstream item;
    std::fstream enemy;

    // ���͂̂��߂ɃI�[�v��������o�͂��o�C�i���ōs��
    stage.open( "mario_field.fmf", std::ios_base::in | std::ios_base::binary );
    enemy.open( "mario_enemy.fmf", std::ios_base::in | std::ios_base::binary );
    item.open( "mario_item.fmf", std::ios_base::in | std::ios_base::binary );

    // �N���X���̏��������s��
    item_->initialize( item );
    enemy_->initalize( enemy );
    field_->initialize( stage );
    player_->initialize();
 
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
                player_->getPositionX(),
                player_->getPositionY(),
                enemy_->getEnemyPosX( i, j ),
                enemy_->getEnemyPosY( i, j ),
                player_->getStatus() ) == 1 )
            {
                int id = enemy_->getId( i, j );

                // �ォ��N���{�[���݂����Ƃ�
                if( id == kKuribo )
                {
                    // ���܂ꂽ��̉��o
                    enemy_->posCollision( i, j );
                    player_->enemyStepon();
                }              
                
                // �ォ��m�R�m�R���݂����Ƃ�
                if( id == kTurtle )
                {
                    // ���܂ꂽ��̉��o
                    player_->enemyStepon();
                    enemy_->posCollision( i, j );
                }

                // �ォ��b�����݂����Ƃ�
                if( id == 113 )
                {
                    // ���܂ꂽ��̉��o
                    player_->enemyStepon();
                    enemy_->shellCollision( i, j );
                }

            }
            else if( pos_col_->getEnemyCollision(
                player_->getPositionX(),
                player_->getPositionY(),
                enemy_->getEnemyPosX( i, j ),
                enemy_->getEnemyPosY( i, j ),
                player_->getStatus() ) == 2 )
            {
                int id = enemy_->getId( i, j );

                if( id == kKuribo )
                {
                    // ���G���Ԓ��͓����蔻������Ȃ�
                    if( player_->getInvincible() == true )
                    {
                        player_->enemyCollision();
                    }
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

                if( id == kKuribo )
                {
                    // ���G���Ԓ��͓����蔻������Ȃ�
                    if( player_->getInvincible() == true )
                    {
                        player_->enemyCollision();
                    }
                }
            }
        }
    }
}

void PlayScene::draw()
{    
    item_->draw(player_->getScrollCnt());
    field_->draw(player_->getScrollCnt());
    enemy_->draw(player_->getScrollCnt());
    player_->draw();
}

void PlayScene::finalize()
{
    // DeleteGraph�Ȃ�
    item_->finalize();
    enemy_->finalize();
    field_->finalize();
    player_->finalize();

    // �������J��new������]
    delete item_;
    delete field_;
    delete player_;
    delete pos_col_;
}