#include "brick.hpp"

void Brick::update()
{
    // 絶対壊れるだけと仮定

    // if( status_ != kMario )
    //{
        // レンガが叩かれたとき
        parts_.Id = 191;

        RECT rect;
        rect.top = parts_.Id / 16 * 64;
        rect.left = parts_.Id % 16 * 64;
        rect.bottom = 64;
        rect.right = 64;
        parts_.rect = rect;
    //}
}