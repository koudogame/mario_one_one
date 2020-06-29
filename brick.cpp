#include "brick.hpp"

void Brick::update(int Status)
{
    if (Status != 0)
    {
        // ƒŒƒ“ƒK‚ª’@‚©‚ê‚½‚Æ‚«
        parts_.Id = 191;

        RECT rect;
        rect.top = parts_.Id / 16 * kSize;
        rect.left = parts_.Id % 16 * kSize;
        rect.bottom = kSize;
        rect.right = kSize;
        parts_.rect = rect;
    }
    else
    {
        base_pos_ = parts_.y;
        parts_.y -= kSize / 4;
        upblock_flag_ = false;
    }
}

void Brick::downBlock()
{
    if( !upblock_flag_ )
    {
        if( parts_.y < base_pos_ )
            parts_.y += 2;
        else
            upblock_flag_ = true;
    }
}
