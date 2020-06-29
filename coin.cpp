#include "coin.hpp"

void Coin::update(int Screenover)
{
    if( !up_ )
    {
        if( jumping_ == kJump )
        {
            jumping_ = kNoJump;
            acceleration_ = -kJumpPower;
            item_.y -= 64;
        }

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
                rect.left = (item_.Id % 16 * kSize) + (coin_animation_ * 32);
                rect.bottom = kSize;
                rect.right = kSize / 2;

                item_.rect = rect;

                coin_animation_ += 1;
                if( coin_animation_ >= 4 )
                    coin_animation_ = 0;
            }

            body_[ kRight ][ kFoot ][ kX ] = (item_.x + (kSize - 10));
            body_[ kRight ][ kFoot ][ kY ] = (item_.y + kSize + 1) + (kSize * 4);

            body_[ kLeft ][ kFoot ][ kX ] = (item_.x + 10);
            body_[ kLeft ][ kFoot ][ kY ] = (item_.y + kSize + 1) + (kSize * 4);

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
