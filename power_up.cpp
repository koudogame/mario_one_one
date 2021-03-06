#include "power_up.hpp"

void Powerup::update( int Screenover )
{
    if( !up_ )
    {
        // 一度だけStatusの確認を行う
        if( punch_ )
        {
            // Status確認し、出すアイテムを選択する
            if( status_ == kMario )
            {
                item_.Id = kMashroom;
                RECT rect;
                rect.top = item_.Id / kLength * kSize;
                rect.left = item_.Id % kLength * kSize;
                rect.bottom = kSize;
                rect.right = kSize;
                item_.rect = rect;

                up_cnt_ += kPunchUp;
                item_.y -= kPunchUp;

                punch_ = false;
            }
            else
            {
                item_.Id = kFlower;
                RECT rect;
                rect.top = item_.Id / kLength * kSize;
                rect.left = item_.Id % kLength * kSize;
                rect.bottom = kSize;
                rect.right = kSize;
                item_.rect = rect;

                up_cnt_ += kPunchUp;
                item_.y -= kPunchUp;

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
            // キノコの時
            if( item_.Id == kMashroom )
            {
                if( Screenover <= item_.x + kSize )
                    item_.x += kSpeed * direction_;      // 常に進む

                    // 足の登録
                body_[ kRight ][ kFoot ][ kX ] = (item_.x + (kSize - kGather));
                body_[ kRight ][ kFoot ][ kY ] = (item_.y + kSize + 1) + kQuadruple;

                body_[ kLeft ][ kFoot ][ kX ] = (item_.x + kGather);
                body_[ kLeft ][ kFoot ][ kY ] = (item_.y + kSize + 1) + kQuadruple;

                int fool_col = Collision::footColl();

                // 足場があるとき
                if( fool_col == 1 )
                {
                    jumping_ = kNoMove;
                    acceleration_ = 0;  // 落下速度

                    int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;

                    if( block_line >= kGroundArray )
                        item_.y = kGround;
                    else
                        item_.y = ((block_line - kControl) * kSize) - 1;

                }
                // 宙に浮いているとき
                else if( fool_col == 2 )
                {
                    jumping_ = kNoJump;

                    if( item_.y > kFallOut )
                    {
                        // アイテムを消す処理を書く
                        jumping_ = kNoMove;

                        item_.Id = kNoBlock;
                        RECT rect;
                        rect.top = item_.Id / kLength * kSize;
                        rect.left = item_.Id % kLength * kSize;
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
                body_[ kRight ][ kShoulder ][ kY ] = (item_.y + kGather) + kQuadruple;
                body_[ kRight ][ kHands ][ kX ] = (item_.x + kSize + 1);
                body_[ kRight ][ kHands ][ kY ] = (item_.y - kGather) + kQuadruple;

                if( turn_ )
                    // 当たり判定のあるとき
                    if( Collision::sideColl( kRight ) == false )
                    {
                        turn_ = false;
                        direction_ *= -1;
                    }

                // 左手の登録
                body_[ kLeft ][ kShoulder ][ kX ] = (item_.x - 1);
                body_[ kLeft ][ kShoulder ][ kY ] = (item_.y + kGather) + kQuadruple;
                body_[ kLeft ][ kHands ][ kX ] = (item_.x - 1);
                body_[ kLeft ][ kHands ][ kY ] = (item_.y - kGather) + kQuadruple;

                if( turn_ )
                    // 当たり判定のあるとき
                    if( Collision::sideColl( kLeft ) == false )
                    {
                        turn_ = false;
                        direction_ *= -1;
                    }
            }
            else if( item_.Id == kFlower )
                // フラワーをきらきらさせる
                flowerAnimation();
        }
    }
}

// 一度しか呼ばないようにするため
void Powerup::flagChange( int Status )
{
    up_ = false;
    jumping_ = kJump;
    status_ = Status;
}

int Powerup::getPosX()
{
    if( !up_flag_ )
    return (item_.x - 1);

    return 0;
}

int Powerup::getPosY()
{
    if( !up_flag_ )
    return (item_.y - 1) + kQuadruple;

    return 0;
}

// マリオと当たったとき
void Powerup::posCollision()
{
    // アイテムを消す処理を書く
    jumping_ = kNoMove;

    item_.y = kFallOut;

    item_.Id = kNoBlock;
    RECT rect;
    rect.top = item_.Id / kLength * kSize;
    rect.left = item_.Id % kLength * kSize;
    rect.bottom = kSize;
    rect.right = kSize;
    item_.rect = rect;
}

// フラワーのきらきらアニメーション
void Powerup::flowerAnimation()
{
    animation_cnt_++;

    if( animation_cnt_ > 2 )
    {
        animation_cnt_ = 0;
        flower_animation_ += 1;

        if( flower_animation_ >= 3 )
            flower_animation_ = 0;
    }

    item_.rect.left = flower_animation_ * kSize;
    item_.rect.right = kSize;
}
