#include "brick.hpp"

void Brick::update()
{
    // ��Ή��邾���Ɖ���

    // if( status_ != kMario )
    //{
        // �����K���@���ꂽ�Ƃ�
        parts_.Id = 191;

        RECT rect;
        rect.top = parts_.Id / 16 * 64;
        rect.left = parts_.Id % 16 * 64;
        rect.bottom = 64;
        rect.right = 64;
        parts_.rect = rect;
    //}
}