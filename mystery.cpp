#include "mystery.hpp"

void Mystery::update( int Status )
{        
    // はてなが叩かれたとき
    if( !stand_by_ )
    {
        // はてなから何もないブロックへ
        if( parts_.Id == kMystery )
        {
            base_pos_ = parts_.y;
            parts_.y -= kBlockUp;
            upblock_flag_ = false;

            parts_.Id = kUsedBlock;
            RECT rect;
            rect.top = kSize;
            rect.left = 0;
            rect.bottom = kSize;
            rect.right = kSize;
            parts_.rect = rect;
        }
    }
    else
    {
        // ハテナブロックのアニメーションの変化
        animation_cnt_++;

        if( animation_cnt_ <= kChangeTime * 3 )
        {
            RECT rect;
            rect.top = kMystery / kLength * kSize;
            rect.left = kMystery % kLength * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            parts_.rect = rect;
        }
        else if( animation_cnt_ <= kChangeTime * 4 )
        {
            RECT rect;
            rect.top = kMystery / kLength * kSize;
            rect.left = (kMystery + 1) % kLength * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            parts_.rect = rect;
        }
        else if( animation_cnt_ <= kChangeTime * 5 )
        {
            RECT rect;
            rect.top = kMystery / kLength * kSize;
            rect.left = (kMystery + 2) % kLength * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            parts_.rect = rect;
        }
        else if( animation_cnt_ <= kChangeTime * 6 )
        {
            RECT rect;
            rect.top = kMystery / kLength * kSize;
            rect.left = (kMystery + 3) % kLength * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            parts_.rect = rect;
        }
        else
            animation_cnt_ = 0;
    }
}

// ブロックをもとの高さに戻す処理
void Mystery::downBlock()
{
    if( !upblock_flag_ )
    {
        if( parts_.y < base_pos_ )
            parts_.y += kDownSpeed;
        else
        upblock_flag_ = true;
    }
}

// 叩かれたら falseへ変更
void Mystery::standby(int x, int y)
{
    stand_by_ = false;
}
