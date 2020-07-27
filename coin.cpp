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
                rect.top = item_.Id / kLength * kSize;
                rect.left = (item_.Id % kLength * kSize) + (coin_animation_ * kHalfSize);
                rect.bottom = kSize;
                rect.right = kHalfSize;

                item_.rect = rect;

                coin_animation_ += 1;
                if( coin_animation_ >= kReset )
                    coin_animation_ = 0;
            }

            // �����̓o�^
            body_[ kRight ][ kFoot ][ kX ] = (item_.x + (kSize - kGather));
            body_[ kRight ][ kFoot ][ kY ] = (item_.y + kSize + 1) + kQuadruple;

            body_[ kLeft ][ kFoot ][ kX ] = (item_.x + kGather);
            body_[ kLeft ][ kFoot ][ kY ] = (item_.y + kSize + 1) + kQuadruple;

            // �u���b�N�Ɠ��������Ƃ�������
            if( Collision::footColl() == 1 )
            {
                item_.Id = kNoBlock;
                RECT rect;
                rect.top    = item_.Id / kLength * kSize;
                rect.left   = item_.Id % kLength * kSize;
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
        rect.top    = kCoin / kLength * kSize;
        rect.left   = (item_.Id % kLength * kSize);
        rect.bottom = kSize;
        rect.right  = kHalfSize;
        item_.rect  = rect;
        item_.x += kLength;
    }
}
