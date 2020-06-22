#include "mystery.hpp"

void Mystery::update(int Status)
{
    // はてなが叩かれたとき
    if( parts_.Id == 48 || parts_.Id == 49 )
    {
        // のちにキノコを出す処理

        // はてなボックスを使用済み
        parts_.Id = 16;

        RECT rect;
        rect.top = parts_.Id / 16 * 64;
        rect.left = parts_.Id % 16 * 64;
        rect.bottom = 64;
        rect.right = 64;
        parts_.rect = rect;
    }
}
