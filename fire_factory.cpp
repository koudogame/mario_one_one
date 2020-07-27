#include "fire_factory.hpp"

void FireFactory::initialize( int PosX, int PosY, int Direction)
{
    // ������ꂽ���̃}���I�̍��W���X�^�[�g�ʒu�Ƃ���
    fire_pos_x_    = PosX + kHalfSize;
    fire_pos_y_    = PosY + kHalfSize - kQuadruple;

    // �}���I�̌����̎󂯓n��
    direction_     = Direction;

    // sideTouch
    side_touch_    = true;

    // �A�j���p�ϐ�������
    animation_     = 0;
    animation_cnt_ = 0;

    explode_cnt_   = 0;
    explode_flag_  = true;
}

void FireFactory::update()
{
    // �ǂ����ɂԂ���܂�
    if( side_touch_ )
    {
        // �t�@�C�A�A�j���[�V����
        animation();            
        
        // ��ɉ��ړ�
        fire_pos_x_ += kSpeed * direction_;

        // �E�T�C�h�̓o�^
        body_[ RL::kRight ][ kShoulder ][ kX ] = fire_pos_x_ + kHalfSize + 1;
        body_[ RL::kRight ][ kShoulder ][ kY ] = (fire_pos_y_ + kDisplace) + kQuadruple;
        body_[ RL::kRight ][ kHands ][ kX ] = fire_pos_x_ + kHalfSize + 1;
        body_[ RL::kRight ][ kHands ][ kY ] = (fire_pos_y_ - kDisplace) + kQuadruple;

        // �����蔻�肪����Ƃ�
        if( !Collision::sideColl( RL::kRight ))
            // �����蔻�菈��
            side_touch_ = false;

        // ���T�C�h�̓o�^
        body_[ RL::kLeft ][ kShoulder ][ kX ] = fire_pos_x_ - 1;
        body_[ RL::kLeft ][ kShoulder ][ kY ] = fire_pos_y_ + kQuadruple + kDisplace;
        body_[ RL::kLeft ][ kHands ][ kX ] = fire_pos_x_ - 1;
        body_[ RL::kLeft ][ kHands ][ kY ] = fire_pos_y_ + kQuadruple - kDisplace;

        // �����蔻�肪����Ƃ�
        if( !Collision::sideColl( RL::kLeft ))
            // �����蔻�菈��
            side_touch_ = false;


        // ���̕����̓o�^(Collision)
        // �E���A�����̓o�^
        body_[ RL::kRight ][ kFoot ][ kX ] = fire_pos_x_ + (kHalfSize - kDisplace);
        body_[ RL::kRight ][ kFoot ][ kY ] = fire_pos_y_ + (kHalfSize + 1) + kQuadruple;

        body_[ RL::kLeft ][ kFoot ][ kX ] = fire_pos_x_ + kDisplace;
        body_[ RL::kLeft ][ kFoot ][ kY ] = fire_pos_y_ + (kHalfSize + 1) + kQuadruple;

        // ���ꂪ����Ƃ�
        if( Collision::fireColl() == 3 )
        {
            jumping_ = kNoMove;

            int block_line = (body_[ RL::kRight ][ kFoot ][ kY ] - 1) / kSize;
            fire_pos_y_ = ((block_line - kControl) * kSize) - kSize;

            if( block_line >= kGroundArray )
                fire_pos_y_ = kGround;

            acceleration_ = 0;  // �������x
            acceleration_ = (-kJumpPower / 2);
        }
        else if( Collision::fireColl() == 1 )
        {
            jumping_ = kNoMove;

            int block_line = (body_[ RL::kRight ][ kFoot ][ kY ] - 1) / kSize;
            fire_pos_y_ = ((block_line - kControl) * kSize) - kSize;

            if( block_line >= kGroundArray )
                fire_pos_y_ = kGround;

            acceleration_ = 0;  // �������x
            acceleration_ = -kJumpPower;
        }
        // ���ɕ����Ă���Ƃ�
        else if( Collision::fireColl() == 2 )
        {
            jumping_ = kNoJump;

            // ���ɕ����Ă���Ƃ�����
            if( jumping_ == kNoJump )
            {
                acceleration_ += kGravity;
                fire_pos_y_ += acceleration_;
            }
        }
    }
    else
        // �Ԃ������Ƃ�
        burnAnimation();
}

void FireFactory::draw( int Texture, const int ScreenOver )
{
    texture_ = Texture;

    int top    = kSextuple;
    int bottom = kHalfSize;

    int left   = (animation_ * kHalfSize);
    int right  = kHalfSize;

    int x = fire_pos_x_ - ScreenOver;

    if(side_touch_)
    DrawRectGraph( x, fire_pos_y_,
        left, top, right, bottom, texture_, TRUE, FALSE );    
    DrawRectGraph( x, fire_pos_y_,
        explosion_[ Rect::kLeft ], explosion_[ Rect::kTop ], explosion_[ Rect::kRight ], explosion_[ Rect::kBottom ],
        texture_, TRUE, FALSE );
}

// ��ʓ��ɂ��邩�m�F����֐�
bool FireFactory::getCheckScreen( const int ScreenOver )
{        
    // FireBall�ƁA��ʂ̑傫��
    int screen_left   = ScreenOver;
    int screen_right  = ScreenOver + kScreenXSize;

    int screen_top    = 0;
    int screen_bottom = kScreenYSize;

    int fire_left     = fire_pos_x_;
    int fire_right    = fire_pos_x_ + kHalfSize;

    int fire_top      = fire_pos_y_;
    int fire_bottom   = fire_pos_y_ + kHalfSize;

    // ��ʓ��ɂ���Ƃ�
    if( (screen_right > fire_left) && (fire_right > screen_left)
        && (screen_bottom > fire_top) && (fire_bottom > screen_top) )
        return true;
    else
    // ��ʊO
    return false;
}

// �t�@�C�A�{�[���̃A�j���[�V�������䂷��֐�
void FireFactory::animation()
{
    animation_cnt_++;

    if( animation_cnt_ >= kAnime )
    {
        animation_cnt_ = 0;
        animation_++;

        if( animation_ >= kLimit )
            animation_ = 0;
    }
}

// �ǂ�������Ɠ��������Ƃ��������N�����֐�
void FireFactory::burnAnimation()
{
    explode_cnt_++;

    if( explode_cnt_ <= kSmall )
    {
        // RECT�̒l��ύX�i�������j
        explosion_[ Rect::kLeft ]   = 0;
        explosion_[ Rect::kTop ]    = kSeptuple;
        explosion_[ Rect::kRight ]  = kSize;
        explosion_[ Rect::kBottom ] = kSize;
    }
    else if( explode_cnt_ <= kBic )
        explosion_[ Rect::kLeft ] = kSize;
    else
        // ��ʂ肵�������(erase)
        explode_flag_ = false;
}

void FireFactory::setFire( bool Fire )
{
    if( !Fire )
    {
        side_touch_ = false;

        if(explode_flag_)
        burnAnimation();
    }
}
