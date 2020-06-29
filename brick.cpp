#include "brick.hpp"

void Brick::update(int Status)
{
    BlockBase::update(Status);

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
}