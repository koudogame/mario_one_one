#include "hata.hpp"

void Hata::upHata( bool End )
{
    if( !End )
    {
        up_cnt_ += 2;
        if( up_cnt_ <= kSize )
            item_.y -= 2;
    }

    item_.x = (kHata * kSize);
}
