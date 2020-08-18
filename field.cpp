#include "field.hpp"

bool Field::initialize( std::fstream& stage )
{
    texture_ = LoadGraph( "Texture/mario_field.png" );

    // �t�@�C���|�C���^��擪�Ɉړ�
    stage.seekg( 0 );

    // �擪8�o�C�g���X�L�b�v
    stage.seekg( 8L );

    stage.read( reinterpret_cast<char*>(&width_), sizeof( int ) );
    stage.read( reinterpret_cast<char*>(&height_), sizeof( int ) );

    // 20�o�C�g�X�L�b�v
    stage.seekg( 20L );

    field_.resize( 2 );

    for( int layer = 0; layer < 2; layer++ )
    {
        for( int i = 0; i < height_; i++ )
        {
            field_[ layer ].push_back( std::vector<BlockBase*>( width_ ) );

            for( int j = 0; j < width_; j++ )
            {
                RECT rect;
                int position_x;
                int position_y;
                int id = 0;

                stage.read( reinterpret_cast<char*>(&id), sizeof( char ) );

                // Id�ɉ����ēo�^

                if( id == kBrick )
                {
                    field_[ layer ][ i ][ j ] = new Brick;      // �����K�̎�
                }
                else if( id == kMystery )
                {
                    field_[ layer ][ i ][ j ] = new Mystery;    // �͂Ăȃ{�b�N�X�̎�
                }
                else
                {
                    field_[ layer ][ i ][ j ] = new BlockBase;  // �x�[�X�ƂȂ锠
                }

                // �`��͈͂�ݒ�
                rect.top = id / kLength * kSize;
                rect.left = id % kLength * kSize;
                rect.bottom = kSize;
                rect.right = kSize;

                // �����Ȃ���̕����̕����� (-n*kSize)
                position_x = (kSize * j);
                position_y = (kSize * i) - kQuadruple;

                field_[ layer ][ i ][ j ]->initialize( id, rect, position_x, position_y );
            }
        }
    }

    return true;
}

void Field::update( PlayerData PlayerData )
{
  
    // �@���ꂽ�E��
    if( PlayerData.break_right.x != 0 || PlayerData.break_right.y != 0 )
    {
        // ��ɉE�̓���o�^
        block_right_.x = PlayerData.break_right.x;
        block_right_.y = PlayerData.break_right.y;

        field_[ 0 ][ PlayerData.break_right.y ][ PlayerData.break_right.x ]->standby( PlayerData.break_right.x, PlayerData.break_right.y );
    }

    // �@���ꂽ����
    if( PlayerData.break_left.x != 0 || PlayerData.break_left.y != 0 )
    {
        block_left_.x = PlayerData.break_left.x;
        block_left_.y = PlayerData.break_left.y;

        field_[ 0 ][ PlayerData.break_left.y ][ PlayerData.break_left.x ]->standby( PlayerData.break_left.x, PlayerData.break_left.y );
    }

    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // ��ɓ����鏀���͂����Ă���
            if( field_[ 0 ][ i ][ j ]->getId() == kBrick || field_[ 0 ][ i ][ j ]->getId() == kMystery || field_[ 0 ][ i ][ j ]->getId() == kNoblock )
            {
                // �X�V���ꂽBlockBase->update()���Ăяo��
                field_[ 0 ][ i ][ j ]->update( PlayerData.player_status );
            }
        }
    }
}

void Field::draw( int ScreenOver )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // ���w�i�̕`��A�c�A�����摜�̐؂���ɍ��킹�ĕ`��
            field_[ 0 ][ i ][ j ]->draw( texture_, ScreenOver );
        }
    }
}

void Field::drawFront( int ScreenOver )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // ���w�i�̕`��A�c�A�����摜�̐؂���ɍ��킹�ĕ`��
            field_[ 1 ][ i ][ j ]->draw( texture_, ScreenOver );
        }
    }

}

void Field::finalize()
{
    // �e�N�X�`���J��
    DeleteGraph( texture_ );

    // �O�����z��J��
    for( int layer = 0; layer < 2; layer++ )
    {
        for( int i = 0; i < height_; i++ )
        {
            for( int j = 0; j < width_; j++ )
            {
                SAFE_DELETE( field_[ layer ][ i ][ j ] );
            }
        }
    }
}

// �������̂œ��������Ƃ����������u���b�N�̊֐����Ăяo��
void Field::downBlock()
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            field_[ 0 ][ i ][ j ]->downBlock();
        }
    }
}

int Field::getId( int PosX, int PosY )
{
    // ID���v�Z���ĕԂ�
    return field_[ 0 ][ PosY ][ PosX ]->getId();
}