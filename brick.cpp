#include "brick.hpp"

void Brick::initialize( const int Id, const RECT Rect, const int X, const int Y )
{
    BlockBase::initialize( Id, Rect, X, Y );

    punch_ = true;
}

void Brick::update(int Status)
{
    if( !stand_by_ )
    {
        if( punch_ )
        {
            if( Status != 0 )
            {
                // レンガが叩かれたとき
                parts_.Id = kNoBlock;
                RECT rect;
                rect.top = kNoBlock / 16 * kSize;
                rect.left = kNoBlock % 16 * kSize;
                rect.bottom = kSize;
                rect.right = kSize;
                parts_.rect = rect;

                // 右頭、初期座標を登録する
                for( int i = 0; i < kPartsNum; i++ )
                {
                    break_parts_[ i ][ kPositionX ] = (pos_x_ * kSize);
                    break_parts_[ i ][ kPositionY ] = (pos_y_ * kSize);
                }

                // ジャンプ力の設定
                acceleration_up_ = -kJumpUp;
                acceleration_down_ = -kJumpDown;

                punch_ = false;
            }
            else
            {
                base_pos_ = parts_.y;
                parts_.y -= kSize / 4;
                upblock_flag_ = false;
                stand_by_ = true;
            }
        }

        // ここからブロックを落下させる処理を組む
        if( !stand_by_ )
        {
            for( int i = 0; i < kPartsNum; i++ )
            {
                // X座標の移動
                if( (i % 2) == 0 )
                    break_parts_[ i ][ kPositionX ] += kSpeed;
                else
                    break_parts_[ i ][ kPositionX ] -= kSpeed;

                // Y座標の移動
                if( i < 2 )
                    break_parts_[ i ][ kPositionY ] += acceleration_up_;
                else
                    break_parts_[ i ][ kPositionY ] += acceleration_down_;
            }

            acceleration_up_ += kGravity;
            acceleration_down_ += kGravity;
        }
    }
}

void Brick::draw( int Texture, int ScreenOver)
{
    BlockBase::draw( Texture, ScreenOver );

    if( !stand_by_ )
    {
        for( int i = 0; i < kPartsNum; i++ )
        {
            int texture_position_x = break_parts_[ i ][ kPositionX ] - ScreenOver;
            int texture_position_y = break_parts_[ i ][ kPositionY ];

            DrawRectGraph(
                (texture_position_x), (texture_position_y - (kSize * 4)),
                (kSize * 3), kSize, (kSize / 2), (kSize / 2), Texture, TRUE, FALSE );
        }
    }
}

void Brick::downBlock()
{
    if( !upblock_flag_ )
    {
        if( parts_.y < base_pos_ )
        {
            parts_.y += 2;
        }
        else          
            upblock_flag_ = true;
    }
}

void Brick::standby(int x, int y)
{
    pos_x_ = x;
    pos_y_ = y;

    stand_by_ = false;
}
