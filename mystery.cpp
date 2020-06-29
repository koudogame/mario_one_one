#include "mystery.hpp"

void Mystery::update(int Status)
{
    // ‚Í‚Ä‚È‚ª’@‚©‚ê‚½‚Æ‚«
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
