#include "coin.hpp"

void Coin::update()
{
    if( up_ == false )
    {
        if( jumping_ == true )
        {
            jumping_ = false;
            acceleration_ = -kJumpPower;
            item_.y -= 64;
        }

        if( jumping_ == false )
        {
            acceleration_ += kGravity;

            // コインを飛ばす
            item_.y += acceleration_;

            body_[ kRight ][ kFoot ][ kX ] = (item_.x + (kSize - 10));
            body_[ kRight ][ kFoot ][ kY ] = (item_.y + kSize + 1) + 256;

            body_[ kLeft ][ kFoot ][ kX ] = (item_.x + 10);
            body_[ kLeft ][ kFoot ][ kY ] = (item_.y + kSize + 1) + 256;

            if( Collision::footColl() == 1 )
            {
                item_.Id = kNoBlock;
                RECT rect;
                rect.top = item_.Id / 16 * 64;
                rect.left = item_.Id % 16 * 64;
                rect.bottom = 64;
                rect.right = 64;
                item_.rect = rect;

                jumping_ = true;
            }
        }
    }
}

void Coin::flagChange( int Status )
{    
    up_ = false;
    jumping_ = true;
    status_ = Status;
}
