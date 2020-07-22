#include "coin.hpp"

void Coin::update(int Screenover)
{
    // ��x����̏���
    if( !up_ )
    {
        // ��ɏオ��͂̕t�^
        if( jumping_ == kJump )
        {
            jumping_ = kNoJump;
            acceleration_ = -kJumpPower;
            item_.y -= kSize;
        }

        // ��ɂ�����ꂽ���̏���
        if( jumping_ == kNoJump )
        {
            acceleration_ += kGravity;

            // �R�C�����΂�
            item_.y += acceleration_;

            // �R�C������
            animation_cnt_++;

            // �R�C���؂�ւ��X�s�[�h
            if( animation_cnt_ >= kChangeSpeed )
            {
                animation_cnt_ = 0;
                RECT rect;
                rect.top = item_.Id / 16 * kSize;
                rect.left = (item_.Id % 16 * kSize) + (coin_animation_ * (kSize / 2));
                rect.bottom = kSize;
                rect.right = kSize / 2;

                item_.rect = rect;

                coin_animation_ += 1;
                if( coin_animation_ >= 4 )
                    coin_animation_ = 0;
            }

            // �����̓o�^
            body_[ kRight ][ kFoot ][ kX ] = (item_.x + (kSize - 10));
            body_[ kRight ][ kFoot ][ kY ] = (item_.y + kSize + 1) + (kSize * 4);

            body_[ kLeft ][ kFoot ][ kX ] = (item_.x + 10);
            body_[ kLeft ][ kFoot ][ kY ] = (item_.y + kSize + 1) + (kSize * 4);

            // �u���b�N�Ɠ��������Ƃ�������
            if( Collision::footColl() == 1 )
            {
                item_.Id = kNoBlock;
                RECT rect;
                rect.top    = item_.Id / 16 * kSize;
                rect.left   = item_.Id % 16 * kSize;
                rect.bottom = kSize;
                rect.right  = kSize;
                item_.rect  = rect;

                jumping_ = kNoMove;
            }
        }
    }
}

// ��x�����������Ă΂Ȃ��悤�ɂ��邽��
void Coin::flagChange( int Status )
{
    if( punch_ )
    {
        punch_   = false;
        up_      = false;
        jumping_ = kJump;
        status_  = Status;

        RECT rect;
        rect.top = kCoin / 16 * kSize;
        rect.left = (item_.Id % 16 * kSize);
        rect.bottom = kSize;
        rect.right = kSize / 2;
        item_.rect = rect;
        item_.x += 16;
    }
}
