#include "field.hpp"

bool Field::initialize( std::fstream& stage )
{
    texture_ = LoadGraph( "Texture/mario_field.png" );

    block_rx_, block_ry_ = 0;
    block_lx_, block_ly_ = 0;

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
                rect.top = id / 16 * kSize;
                rect.left = id % 16 * kSize;
                rect.bottom = 64;
                rect.right = 64;

                // �����Ȃ���̕����̕����� (-n*64)
                position_x = (64 * j);
                position_y = (64 * i) - 256;

                field_[ layer ][ i ][ j ]->initialize( id, rect, position_x, position_y );
            }
        }
    }

    return true;
}

void Field::update( int Brx, int Bry, int Blx, int Bly, int Status )
{
    // �@���ꂽ�E��
    if( Brx != 0 || Bry != 0 )
    {
        // ��ɉE�̓���o�^
        block_rx_ = Brx;
        block_ry_ = Bry;

        field_[ 0 ][ Bry ][ Brx ]->standby(Brx, Bry);
    }

    // �@���ꂽ����
    if( Blx != 0 || Bly != 0 )
    {
            block_lx_ = Blx;
            block_ly_ = Bly;

            field_[ 0 ][ Bly ][ Blx ]->standby(Blx, Bly);
    }

    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // ��ɓ����鏀���͂����Ă���
            if( field_[ 0 ][ i ][ j ]->getId() == kBrick || field_[ 0 ][ i ][ j ]->getId() == kMystery || field_[ 0 ][ i ][ j ]->getId() == kNoblock )
            {
                // �X�V���ꂽBlockBase->update()���Ăяo��
                field_[ 0 ][ i ][ j ]->update( Status );
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