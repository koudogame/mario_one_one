#include "coin.hpp"

void Coin::update(int Screenover)
{
    // 一度きりの処理
    if( !up_ )
    {
        // 上に上がる力の付与
        if( jumping_ == kJump )
        {
            jumping_ = kNoJump;
            acceleration_ = -kJumpPower;
            item_.y -= kSize;
        }

        // 上にあげられた時の処理
        if( jumping_ == kNoJump )
        {
            acceleration_ += kGravity;

            // コインを飛ばす
            item_.y += acceleration_;

            // コインを回す
            animation_cnt_++;

            // コイン切り替えスピード
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

            // 足元の登録
            body_[ kRight ][ kFoot ][ kX ] = (item_.x + (kSize - 10));
            body_[ kRight ][ kFoot ][ kY ] = (item_.y + kSize + 1) + (kSize * 4);

            body_[ kLeft ][ kFoot ][ kX ] = (item_.x + 10);
            body_[ kLeft ][ kFoot ][ kY ] = (item_.y + kSize + 1) + (kSize * 4);

            // ブロックと当たったとき消える
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

// 一度しか処理を呼ばないようにするため
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
