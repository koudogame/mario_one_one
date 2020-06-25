#include "power_up.hpp"

void Powerup::update( int Screenover )
{
    if( !up_ )
    {
        // 一度だけStatusの確認を行う
        if( punch_ )
        {
            // Status確認
            if( status_ == 0 )
            {
                item_.Id = kMashroom;
                RECT rect;
                rect.top = item_.Id / 16 * kSize;
                rect.left = item_.Id % 16 * kSize;
                rect.bottom = kSize;
                rect.right = kSize;
                item_.rect = rect;

                punch_ = false;
            }
            else
            {
                item_.Id = kFlower;
                RECT rect;
                rect.top = item_.Id / 16 * kSize;
                rect.left = item_.Id % 16 * kSize;
                rect.bottom = kSize;
                rect.right = kSize;
                item_.rect = rect;

                punch_ = false;
            }
        }

        // ブロックの上に出切るまで
        if( up_flag_ )
        {
            if( up_cnt_ <= kSize )
            {
                up_cnt_++;
                item_.y--;
            }
            else
                up_flag_ = false;
        }
        else
        {
            if( item_.Id == kMashroom )
            {
                if( Screenover <= item_.x + kSize )
                    item_.x += kSpeed * direction_;      // 常に進む

                    // 足の登録
                body_[ kRight ][ kFoot ][ kX ] = (item_.x + (kSize - 10));
                body_[ kRight ][ kFoot ][ kY ] = (item_.y + kSize + 1) + (kSize * 4);

                body_[ kLeft ][ kFoot ][ kX ] = (item_.x + 10);
                body_[ kLeft ][ kFoot ][ kY ] = (item_.y + kSize + 1) + (kSize * 4);

                // 足場があるとき
                if( Collision::footColl() == 1 )
                {
                    jumping_ = kNoMove;
                    acceleration_ = 0;  // 落下速度

                    int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;
                    item_.y = ((block_line - 4) * kSize) - 1;

                    if( block_line >= 14 )
                        item_.y = kGround;
                }
                // 宙に浮いているとき
                else if( Collision::footColl() == 2 )
                {
                    jumping_ = kNoJump;

                    if( item_.y > 670 )
                    {
                        // アイテムを消す処理を書く
                        jumping_ = kNoMove;

                        item_.Id = kNoBlock;
                        RECT rect;
                        rect.top = item_.Id / 16 * kSize;
                        rect.left = item_.Id % 16 * kSize;
                        rect.bottom = kSize;
                        rect.right = kSize;
                        item_.rect = rect;
                    }

                    // 宙に浮いているとき落下
                    if( jumping_ == kNoJump )
                    {
                        acceleration_ += kGravity;
                        item_.y += acceleration_;
                    }
                }

                // 右手の登録
                body_[ kRight ][ kShoulder ][ kX ] = (item_.x + kSize + 1);
                body_[ kRight ][ kShoulder ][ kY ] = (item_.y + 10) + (kSize * 4);
                body_[ kRight ][ kHands ][ kX ] = (item_.x + kSize + 1);
                body_[ kRight ][ kHands ][ kY ] = (item_.y - 10) + (kSize * 4);

                // 当たり判定のあるとき
                if( Collision::sideColl( kRight ) == false )
                    direction_ *= -1;

                // 左手の登録
                body_[ kLeft ][ kShoulder ][ kX ] = (item_.x - 1);
                body_[ kLeft ][ kShoulder ][ kY ] = (item_.y + 10) + (kSize * 4);
                body_[ kLeft ][ kHands ][ kX ] = (item_.x - 1);
                body_[ kLeft ][ kHands ][ kY ] = (item_.y - 10) + (kSize * 4);

                // 当たり判定のあるとき
                if( Collision::sideColl( kLeft ) == false )
                    direction_ *= -1;
            }
        }
    }
}

void Powerup::flagChange( int Status )
{
    up_ = false;
    jumping_ = kJump;
    status_ = Status;
}

int Powerup::getPosX()
{
    return (item_.x - 1);
}

int Powerup::getPosY()
{
    return (item_.y - 1) + (kSize * 4);
}

void Powerup::posCollision()
{
    // アイテムを消す処理を書く
    jumping_ = kNoMove;

    item_.y = 670;

    item_.Id = kNoBlock;
    RECT rect;
    rect.top = item_.Id / 16 * kSize;
    rect.left = item_.Id % 16 * kSize;
    rect.bottom = kSize;
    rect.right = kSize;
    item_.rect = rect;
}
