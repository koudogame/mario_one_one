#include "ball_management.hpp"

void BallManagement::initialize()
{
    texture_ = LoadGraph( "Texture/mario_item.png" );
    push_create_fire_ = 0;
}

void BallManagement::update( int PosX, int PosY, int Status, int Direction, bool GameOver )
{
    // �}���I���S�[�����Ă��Ȃ��Ƃ�
    if( GameOver )
    {
        // �{�^���������ꂽ�Ƃ� ���AFireMario�̎�
        if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4) == 0 )
            push_create_fire_++;
        else
        push_create_fire_ = 0;

        if( push_create_fire_ == 1 )
        {
            if( Status == 2 )
            {
                // �V�����ǉ����ē�����
                fire_.push_back( new FireFactory( field_ ) );
                fire_.back()->initialize( PosX, PosY, Direction );
            }
        }
    }

    // �v�f������Fire�𓮂���
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->update();                                 // *itr�A���[���Z�q()������
    }
}

void BallManagement::draw(const int ScreenOver)
{
    // �v�f������Fire��`�悷��
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->draw( texture_, ScreenOver );             // *itr�A���[���Z�q()������
    }
}

void BallManagement::finalize()
{
    DeleteGraph( texture_ );
}

int BallManagement::getFirePosX(int Num)
{
        return fire_[Num]->getFirePosX();                 // *itr�A���[���Z�q()������
}

int BallManagement::getFirePosY(int Num)
{
        return fire_[Num]->getFirePosY();                 // *itr�A���[���Z�q()������
}

int BallManagement::getSize()
{
    return fire_.size();                                  // Fire�̗v�f�̐���Ԃ�
}

void BallManagement::posCheck( const int ScrollCnt)
{
    // ���ꂼ�ꎩ���ŉ�ʓ��ɂ��邩�m�F���s��
    for( auto itr = fire_.begin(); itr != fire_.end();  )
    {
        // ��ʊO��Fireball������Ƃ�
        if( !(*itr)->getCheckScreen( ScrollCnt ) )
        {
            size_t index = std::distance( fire_.begin(), itr );
            SAFE_DELETE( fire_[ index ] );
            itr = fire_.erase( itr );                     // �l�߂�Ƃ��i�����Ƃ��j
        }
        else
            itr++;                                        // �l�߂Ȃ��Ƃ��i�����Ȃ��Ƃ��j
    }
}

void BallManagement::enemyCollision( int Index )
{
    // �����G�Ɠ��������Ƃ������鏈�������s
    SAFE_DELETE( fire_[ Index ] );
    fire_.erase( fire_.begin() + Index );
}
