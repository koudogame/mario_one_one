#include "brick.hpp"

void Brick::initialize( const int Id, const RECT Rect, const int X, const int Y )
{
    // ベースの初期化
    BlockBase::initialize( Id, Rect, X, Y );

    // 叩かれていない状態
    punch_ = true;
}

void Brick::update(int Status)
{
    // 叩かれたとき
    if( !stand_by_ )
    {
        // 一度きりの処理
        if( punch_ )
        {
            // マリオじゃないとき
            if( Status != kMario )
            {
                // レンガが叩かれたとき
                parts_.Id = kNoBlock;
                RECT rect;
                rect.top = kNoBlock / kLength * kSize;
                rect.left = kNoBlock % kLength * kSize;
                rect.bottom = kSize;
                rect.right = kSize;
                parts_.rect = rect;

                // 右頭、初期座標を登録する
                for( int i = 0; i < kBodyParts; i++ )
                {
                    break_parts_[ i ][ kX ] = (pos_x_ * kSize);
                    break_parts_[ i ][ kY ] = (pos_y_ * kSize);
                }

                // ジャンプ力の設定
                acceleration_up_ = -kJumpUp;
                acceleration_down_ = -kJumpDown;

                punch_ = false;
            }
            else
            {
                base_pos_ = parts_.y;
                parts_.y -= kSize / kControl;
                upblock_flag_ = false;
                stand_by_ = true;
            }
        }

        // ここからブロックを落下させる処理を組む
        if( !stand_by_ )
        {
            for( int i = 0; i < kBodyParts; i++ )
            {
                // X座標の移動
                if( (i % 2) == 0 )
                    break_parts_[ i ][ kX ] += kSpeed;
                else
                    break_parts_[ i ][ kX ] -= kSpeed;

                // Y座標の移動
                if( i < 2 )
                    break_parts_[ i ][ kY ] += acceleration_up_;
                else
                    break_parts_[ i ][ kY ] += acceleration_down_;
            }

            // ジャンプ力を付与
            acceleration_up_ += kGravity;
            acceleration_down_ += kGravity;
        }
    }
}

// 描画処理
void Brick::draw( int Texture, int ScreenOver)
{
    // ベースの処理も呼ぶ
    BlockBase::draw( Texture, ScreenOver );

    if( !stand_by_ )
    {
        for( int i = 0; i < kBodyParts; i++ )
        {
            int texture_position_x = break_parts_[ i ][ kX ] - ScreenOver;
            int texture_position_y = break_parts_[ i ][ kY ];

            DrawRectGraph(
                (texture_position_x), (texture_position_y - kQuadruple),
                kTripleSize, kSize, kHalfSize, kHalfSize, Texture, TRUE, FALSE );
        }
    }
}

// 叩かれたとき下に下げる
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

// 叩かれたら falseへ変更
void Brick::standby(int x, int y)
{
    pos_x_ = x;
    pos_y_ = y;

    stand_by_ = false;
}
