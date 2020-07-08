#include "ball_management.hpp"

void BallManagement::initialize()
{
    texture_ = LoadGraph( "Texture/mario_item.png" );
}

void BallManagement::update( int PosX, int PosY, int Status, int Direction )
{
    // �{�^���������ꂽ�Ƃ�
    // ���AFireMario�̎�
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_X) == 0 )
    {
        if( Status == 2 )
        {
            // �V�����ǉ����ē�����
            fire_.push_back( new FireFactory( field_ ) );
            fire_.back()->initialize( PosX, PosY, Direction );
        }
    }

    // �v�f������Fire�𓮂���
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->update();                            // *itr�A���[���Z�q()������
    }
}

void BallManagement::draw(const int ScreenOver)
{
    // �v�f������Fire��`�悷��
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->draw( texture_, ScreenOver );        // *itr�A���[���Z�q()������
    }
}

void BallManagement::finalize()
{
    DeleteGraph( texture_ );
}
