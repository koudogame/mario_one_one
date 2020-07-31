#include "xinput.hpp"

int Xinput::xinput( uint32_t Button )
{
    // すべてのビット状態保存
    bit_ = GetJoypadInputState( DX_INPUT_PAD1 );

    // 過去OFF = 0, 過去ON = 1;
    int past_check = past_bit_ & Button;

    // 今OFF = 0, 今ON = 1;
    int now_check = bit_ & Button;

    // 過去OFF, 今ON
    if( past_check == 0 )
    {
        past_bit_ = bit_;
        return kPress;
    }

    // 過去ON, 今ON
    if( past_check == 1 )
    {
        past_bit_ = bit_;
        return kHold;
    }

    // 過去ON, 今OFF
    if( past_check == 1 && now_check == 0 )
    {
        past_bit_ = bit_;
        return kRelease;
    }

    // その他
    past_bit_ = bit_;
    return kNothing;
}

int Xinput::bit_ = 0;      // クラス変数定義
int Xinput::past_bit_ = 0; // クラス変数定義