#include "castle_flag.hpp"

void CastleFlag::upHata( bool End )
{
    // マリオが消えたのを確認してから旗を掲げる
    if( !End )
    {
        up_cnt_ += 2;
        if( up_cnt_ <= kSize )
            item_.y -= 2;
    }

    item_.x = (kFlag * kSize);
}
