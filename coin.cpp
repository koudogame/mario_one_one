#include "coin.hpp"

void Coin::update()
{
    if( up_ == false )
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

            // ƒRƒCƒ“‚ð”ò‚Î‚·
            item_.y += acceleration_;

            body_[ kRight ][ kFoot ][ kX ] = (item_.x + (kSize - 10));
            body_[ kRight ][ kFoot ][ kY ] = (item_.y + kSize + 1) + 256;

            body_[ kLeft ][ kFoot ][ kX ] = (item_.x + 10);
            body_[ kLeft ][ kFoot ][ kY ] = (item_.y + kSize + 1) + 256;

            if( Collision::footColl() == 1 )
            {
                item_.Id = kNoBlock;
                RECT rect;
                rect.top    = item_.Id / 16 * 64;
                rect.left   = item_.Id % 16 * 64;
                rect.bottom = 64;
                rect.right  = 64;
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
    }
}
