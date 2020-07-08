#include "fire_factory.hpp"

void FireFactory::initialize( int PosX, int PosY, int Direction)
{
    // ������ꂽ���̃}���I�̍��W���X�^�[�g�ʒu�Ƃ���
    fire_pos_x_ = PosX + (kSize / 2);
    fire_pos_y_ = PosY - (kSize * 4) + (kSize / 2);

    // �}���I�̌����̎󂯓n��
    direction_ = Direction;

    // �A�j���p�ϐ�������
    animation_ = 0;
    animation_cnt_ = 0;
}

void FireFactory::update()
{
    animation();            // �t�@�C�A�{�[���A�j���[�V����
    fire_pos_x_ += kSpeed * direction_;

    // ���̕����̓o�^(Collision)
    // �E���A�����̓o�^
    body_[ kRight ][ kFoot ][ kX ] = fire_pos_x_ + ((kSize / 2) - 5);
    body_[ kRight ][ kFoot ][ kY ] = fire_pos_y_ + ((kSize / 2) + 1) + (kSize * 4);

    body_[ kLeft ][ kFoot ][ kX ] = fire_pos_x_ + 5;
    body_[ kLeft ][ kFoot ][ kY ] = fire_pos_y_ + ((kSize / 2) + 1) + (kSize * 4);

            // ���ꂪ����Ƃ�
            if( Collision::footColl() == 1 )
            {
                jumping_ = kNoMove;

                int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;
                fire_pos_y_ = ((block_line - 4) * kSize) - 1;

                if( block_line >= 14 )
                    fire_pos_y_ = kGround;

                acceleration_ = 0;  // �������x
                acceleration_ = -kJumpPower;
            }
            // ���ɕ����Ă���Ƃ�
            else if( Collision::footColl() == 2 )
            {
                jumping_ = kNoJump;

                if( fire_pos_y_ > 670 )
                    jumping_ = kNoMove;

                // ���ɕ����Ă���Ƃ�����
                if( jumping_ == kNoJump )
                {
                    acceleration_ += kGravity;
                    fire_pos_y_ += acceleration_;
                }
            }
}

void FireFactory::draw( int Texture, const int ScreenOver )
{
    texture_ = Texture;

    int top    = kSize * 6;
    int bottom = kSize / 2;

    int left   = (animation_ * (kSize / 2));
    int right  = kSize / 2;

    int x = fire_pos_x_ - ScreenOver;

    DrawRectGraph( x, fire_pos_y_,
        left, top, right, bottom, texture_, TRUE, FALSE );
}

void FireFactory::animation()
{
    animation_cnt_++;

    if( animation_cnt_ >= kAnime )
    {
        animation_cnt_ = 0;
        animation_++;

        if( animation_ >= 4 )
            animation_ = 0;
    }
}
