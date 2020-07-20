#include "enemy.hpp"

Enemy::Enemy( Field* Field )
{
    field_ = Field;
}

void Enemy::initalize( std::fstream& FieldEnemy )
{
    texture_ = LoadGraph( "texture/mario_enemy.png" );

    // �t�@�C���|�C���^��擪�Ɉړ�
    FieldEnemy.seekg( 0 );

    // �擪�o�C�g���X�L�b�v
    FieldEnemy.seekg(8L);

    FieldEnemy.read( reinterpret_cast<char*>(&width_), sizeof( int ) );
    FieldEnemy.read( reinterpret_cast<char*>(&height_), sizeof( int ) );

    // 20�o�C�g�X�L�b�v
    FieldEnemy.seekg( 20L );

    enemy_.resize( 2 );

    for( int i = 0; i < height_; i++ )
    {
        enemy_[ 0 ].push_back( std::vector<EnemyBase*>( width_ ) );

        for( int j = 0; j < width_; j++ )
        {
            RECT rect;
            int position_x;
            int position_y;
            int id = 0;

            FieldEnemy.read( reinterpret_cast<char*>(&id), sizeof( char ) );

            // �e�z��ɏ���new����

            if( id == kKuribo )
                enemy_[ 0 ][ i ][ j ] = new Kuribo( field_ );   // �N���{�[
            else if( id == kTurtle )
                enemy_[ 0 ][ i ][ j ] = new Turtle( field_ );   // �m�R�m�R
            else
                enemy_[ 0 ][ i ][ j ] = new EnemyBase( field_ );// �x�[�X


            // �`��͈͂�ݒ�
            rect.top = id / 16 * kSize;
            rect.left = id % 16 * kSize;
            rect.bottom = kSize;
            rect.right = kSize;

            // �����Ȃ���̕����̕����� (-n*64)
            position_x = (kSize * j);
            position_y = (kSize * i) - (kSize * 4);

            enemy_[ 0 ][ i ][ j ]->initialize( id, rect, position_x, position_y );
        }
    }
}

void Enemy::update( int ScreenOver )
{  
    // ���update()�͌Ă΂��
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // �n����ScreenOver�ňړ����邩�𔻒肳����
            enemy_[ 0 ][ i ][ j ]->update( ScreenOver );
        }
    }
}

void Enemy::draw( int ScreenOver )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // ���w�i�̕`��A�c�A�����摜�̐؂���ɍ��킹�ĕ`��
            enemy_[ 0 ][ i ][ j ]->draw( texture_, ScreenOver );
        }
    }
}

void Enemy::finalize()
{
    // �e�N�X�`���J��
    DeleteGraph( texture_ );

    // �O�����z��J��
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            SAFE_DELETE( enemy_[ 0 ][ i ][ j ] );
        }
    }
}

// �|�W�V������񂪃}���I�Ɠ��������Ƃ��ɌĂ΂��֐�
void Enemy::posCollision( int i, int j, int Touch )
{
    enemy_[ 0 ][ i ][ j ]->posCollision(Touch);
}

// �b����ԂŏՓ˂����Ƃ��ɌĂ΂��֐�
void Enemy::shellCollision( int i, int j )
{
    enemy_[ 0 ][ i ][ j ]->shellCollision();
}

// �t�@�C�A�{�[���ƏՓ˂����Ƃ��ɌĂ΂��֐�
void Enemy::fireCollision( int i, int j )
{
    enemy_[ 0 ][ i ][ j ]->fireCollision();
}

// �|�W�V�������Ԃ��������ύX����Ƃ��ɌĂ΂��֐�
void Enemy::changeDirection( int i, int j )
{
    enemy_[ 0 ][ i ][ j ]->changeDirection();
}
