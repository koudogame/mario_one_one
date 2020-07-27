#include "ball_management.hpp"

void BallManagement::initialize()
{
    texture_          = LoadGraph( "Texture/mario_item.png" );
    push_create_fire_ = 0;

    create_cnt_       = 0;
    create_flag_      = true;
}

void BallManagement::update( int TotalX, int TotalY, int Status, int Direction, bool GameOver, int PosY )
{
    // ���ˉ\���
    if( GameOver && PosY <= kEndline )
    {
        // �{�^���������ꂽ�Ƃ�
        if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4) == 0 || CheckHitKey( KEY_INPUT_B ) == 1 )
            push_create_fire_++;
        else
            push_create_fire_ = 0; // ������Ă��Ȃ��ԏ�����


        // �{�^���������ꂽ�u��
        if( push_create_fire_ == 1 )
            createFire( TotalX, TotalY, Status, Direction );

        // ���ԊǗ�
        if( !create_flag_ )
            create_cnt_++;

        // �A�������Ԋu�ɐ���
        if( create_cnt_ >= kStopper )
        {
            create_cnt_ = 0;
            create_flag_ = true;
        }
    }

    // �v�f������FireBall��update()���Ăяo��
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->update();
    }
}

void BallManagement::draw(const int ScreenOver)
{
    // �v�f������FireBall��draw()���Ăяo��
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->draw( texture_, ScreenOver );
    }
}

void BallManagement::finalize()
{
    DeleteGraph( texture_ );
}

int BallManagement::getFirePosX(int Num)
{
        return fire_[Num]->getFirePosX();
}

int BallManagement::getFirePosY(int Num)
{
        return fire_[Num]->getFirePosY();
}

int BallManagement::getSize()
{
    return static_cast<int>(fire_.size());                // Fire�̗v�f�̐���Ԃ�
}

// �V�����������鏈��
void BallManagement::createFire( int TotalX, int TotalY, int Status, int Direction )
{
    size_t index = std::distance( fire_.begin(), fire_.end() );

    // �S�܂œ������ˉ\
    if( index < kBallLimit )
    {
        // �܂��������Ă��Ȃ�������쐬
        if( create_flag_ )
        {
            // �t�@�C�A�}���I�̂Ƃ�
            if( Status == kFireMario )
            {
                // �V�����ǉ����ē�����
                fire_.push_back( new FireFactory( field_ ) );
                fire_.back()->initialize( TotalX, TotalY, Direction );

                create_flag_ = false;
            }
        }
    }
}


void BallManagement::sideCheck()
{
    for( auto itr = fire_.begin(); itr != fire_.end(); )
    {
        if( !(*itr)->getExplode() )
        {
            size_t index = std::distance( fire_.begin(), itr );
            SAFE_DELETE( fire_[ index ] );
            itr = fire_.erase( itr );   // �l�߂�Ƃ��i�����Ƃ��j
        }
        else
            itr++;                      // �l�߂Ȃ��Ƃ��i�����Ȃ��Ƃ��j
    }
}

void BallManagement::posCheck( const int ScrollCnt)
{
    // ���ꂼ�ꎩ���ŉ�ʓ��ɂ��邩�m�F���s��
    for( auto itr = fire_.begin(); itr != fire_.end();  )
    {
        // ��ʊO��Fireball������Ƃ�
        if( !(*itr)->getCheckScreen( ScrollCnt ) )
        {
            // �z��̐擪����ʒu���v�Z���j������
            size_t index = std::distance( fire_.begin(), itr );
            SAFE_DELETE( fire_[ index ] );
            itr = fire_.erase( itr );   // �l�߂�Ƃ��i�����Ƃ��j
        }
        else
            itr++;                      // �l�߂Ȃ��Ƃ��i�����Ȃ��Ƃ��j
    }
}

void BallManagement::enemyCollision( int Index )
{
    // �����G�Ɠ��������Ƃ������鏈�������s
    fire_[ Index ]->setFire( false );

    if( !fire_[ Index ]->getExplode() )
    {
        SAFE_DELETE( fire_[ Index ] );
        fire_.erase( fire_.begin() + Index );
    }
}