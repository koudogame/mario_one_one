#include "mystery.hpp"

void Mystery::update(int Status)
{
    // �͂ĂȂ��@���ꂽ�Ƃ�
    if( parts_.Id == 48 || parts_.Id == 49 )
    {
        // �̂��ɃL�m�R���o������

        // �͂Ăȃ{�b�N�X���g�p�ς�
        parts_.Id = 16;

        RECT rect;
        rect.top = parts_.Id / 16 * 64;
        rect.left = parts_.Id % 16 * 64;
        rect.bottom = 64;
        rect.right = 64;
        parts_.rect = rect;
    }
}
