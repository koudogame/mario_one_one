#include "mystery.hpp"

void Mystery::update( int Status )
{        
    // ‚Í‚Ä‚È‚ª’@‚©‚ê‚½‚Æ‚«
    if( !stand_by_ )
    {
        if( parts_.Id == kMystery )
        {
            base_pos_ = parts_.y;
            parts_.y -= kSize / 4;
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
        animation_cnt_++;

        if( animation_cnt_ <= kChangeTime * 3 )
        {
            RECT rect;
            rect.top = kMystery / 16 * kSize;
            rect.left = kMystery % 16 * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            parts_.rect = rect;
        }
        else if( animation_cnt_ <= kChangeTime * 4 )
        {
            RECT rect;
            rect.top = kMystery / 16 * kSize;
            rect.left = (kMystery + 1) % 16 * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            parts_.rect = rect;
        }
        else if( animation_cnt_ <= kChangeTime * 5 )
        {
            RECT rect;
            rect.top = kMystery / 16 * kSize;
            rect.left = (kMystery + 2) % 16 * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            parts_.rect = rect;
        }
        else if( animation_cnt_ <= kChangeTime * 6 )
        {
            RECT rect;
            rect.top = kMystery / 16 * kSize;
            rect.left = (kMystery + 3) % 16 * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            parts_.rect = rect;
        }
        else
            animation_cnt_ = 0;
    }
}

void Mystery::downBlock()
{
    if( !upblock_flag_ )
    {
        if( parts_.y < base_pos_ )
            parts_.y += 2;
        else
        upblock_flag_ = true;
    }
}

void Mystery::standby(int x, int y)
{
    stand_by_ = false;
}
