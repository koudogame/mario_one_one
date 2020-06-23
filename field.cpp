#include "field.hpp"

constexpr int kBlocksize = 64;

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

    for( int i = 0; i < height_; i++ )
    {
        field_[ 0 ].push_back( std::vector<BlockBase*>( width_ ) );

        for( int j = 0; j < width_; j++ )
        {
            RECT rect;
            int position_x;
            int position_y;
            int id = 0;

            stage.read( reinterpret_cast<char*>(&id), sizeof( char ) );

            if( id == kBrick )
            {
                field_[ 0 ][ i ][ j ] = new Brick;
            }
            else if( id == kMystery )
            {
                field_[ 0 ][ i ][ j ] = new Mystery;
            }
            else
            {
                field_[ 0 ][ i ][ j ] = new BlockBase;
            }

            // �`��͈͂�ݒ�
            rect.top = id / 16 * kBlocksize;
            rect.left = id % 16 * kBlocksize;
            rect.bottom = 64;
            rect.right = 64;

            // �����Ȃ���̕����̕����� (-n*64)
            position_x = (64 * j);
            position_y = (64 * i) - 256;

            field_[ 0 ][ i ][ j ]->initialize( id, rect, position_x, position_y );
        }
    }

    return true;
}

void Field::update(int Brx, int Bry, int Blx, int Bly, int Status)
{
    // �@���ꂽ�E����update()���Ă�
    if( Brx != 0 || Bry != 0 )
    {
        // �X�V���ꂽBlockBase->update()���Ăяo��
        field_[ 0 ][ Bry ][ Brx ]->update(Status);
    }

    // �@���ꂽ������update()���Ă�
    if( Blx != 0 || Bly != 0 )
    {
        // �X�V���ꂽBlockBase->update()���Ăяo��
        field_[ 0 ][ Bly ][ Blx ]->update(Status);
    }
}

void Field::draw(int ScreenOver)
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

void Field::finalize()
{
    // �e�N�X�`���J��
    DeleteGraph( texture_ );

    // �O�����z��J��
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            SAFE_DELETE( field_[ 0 ][ i ][ j ] );
        }
    }
}

int Field::getId( int PosX, int PosY )
{
    // ID���v�Z���ĕԂ�
    return field_[ 0 ][ PosY ][ PosX ]->getId();
}