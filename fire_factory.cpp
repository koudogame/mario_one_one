#include "fire_factory.hpp"

void FireFactory::initialize( int PosX, int PosY, int Direction)
{
    // ������ꂽ���̃}���I�̍��W���X�^�[�g�ʒu�Ƃ���
    fire_position_.x    = PosX + kHalfSize;
    fire_position_.y    = PosY + kHalfSize - kQuadruple;

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
        fire_position_.x += kSpeed * direction_;

        // �E�T�C�h�̓o�^
        body_[ kRight ][ kShoulder ][ kX ] = fire_position_.x + kHalfSize + 1;
        body_[ kRight ][ kShoulder ][ kY ] = (fire_position_.y + kDisplace) + kQuadruple;
        body_[ kRight ][ kHands ][ kX ] = fire_position_.x + kHalfSize + 1;
        body_[ kRight ][ kHands ][ kY ] = (fire_position_.y - kDisplace) + kQuadruple;

        // �����蔻�肪����Ƃ�
        if( !Collision::sideColl( kRight ))
            // �����蔻�菈��
            side_touch_ = false;

        // ���T�C�h�̓o�^
        body_[ kLeft ][ kShoulder ][ kX ] = fire_position_.x - 1;
        body_[ kLeft ][ kShoulder ][ kY ] = fire_position_.y + kQuadruple + kDisplace;
        body_[ kLeft ][ kHands ][ kX ] = fire_position_.x - 1;
        body_[ kLeft ][ kHands ][ kY ] = fire_position_.y + kQuadruple - kDisplace;

        // �����蔻�肪����Ƃ�
        if( !Collision::sideColl( kLeft ))
            // �����蔻�菈��
            side_touch_ = false;


        // ���̕����̓o�^(Collision)
        // �E���A�����̓o�^
        body_[ kRight ][ kFoot ][ kY ] = fire_position_.y + (kHalfSize + 1) + kQuadruple;
        body_[ kRight ][ kFoot ][ kX ] = fire_position_.x + (kHalfSize - kDisplace);

        body_[ kLeft ][ kFoot ][ kX ] = fire_position_.x + kDisplace;
        body_[ kLeft ][ kFoot ][ kY ] = fire_position_.y + (kHalfSize + 1) + kQuadruple;

        int fire_col = Collision::fireColl();

        // ���ꂪ����Ƃ�
        if( fire_col == 3 )
        {
            jumping_ = kNoMove;

            int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;
            fire_position_.y = ((block_line - kControl) * kSize) - kSize;

            if( block_line >= kGroundArray )
                fire_position_.y = kGround;

            acceleration_ = 0;  // �������x
            acceleration_ = (-kJumpPower / 2);
        }
        else if( fire_col == 1 )
        {
            jumping_ = kNoMove;

            int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;
            fire_position_.y = ((block_line - kControl) * kSize) - kSize;

            if( block_line >= kGroundArray )
                fire_position_.y = kGround;

            acceleration_ = 0;  // �������x
            acceleration_ = -kJumpPower;
        }
        // ���ɕ����Ă���Ƃ�
        else if( fire_col == 2 )
        {
            jumping_ = kNoJump;

            // ���ɕ����Ă���Ƃ�����
            if( jumping_ == kNoJump )
            {
                acceleration_ += kGravity;
                fire_position_.y += acceleration_;
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

    int x = fire_position_.x - ScreenOver;

    if(side_touch_)
    DrawRectGraph( x, fire_position_.y,
        left, top, right, bottom, texture_, TRUE, FALSE );    
    DrawRectGraph( x, fire_position_.y,
        rect_.left, rect_.top, rect_.right, rect_.bottom,
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

    int fire_left     = fire_position_.x;
    int fire_right    = fire_position_.x + kHalfSize;

    int fire_top      = fire_position_.y;
    int fire_bottom   = fire_position_.y + kHalfSize;

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
        rect_.left   = 0;
        rect_.right  = kSize;
        rect_.top    = kSeptuple;
        rect_.bottom = kSize;
    }
    else if( explode_cnt_ <= kBic )
        rect_.left   = kSize;
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
