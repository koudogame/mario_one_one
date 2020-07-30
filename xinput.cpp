#include "xinput.hpp"

int Xinput::XInput( uint32_t Button )
{
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & Button) == 0 )
        check_++;
    else
        check_ = 0;

    if( check_ == kPress )
        return kPress;

    else if( check_ >= kHold )
        return kHold;

    return kNothing;
}

int Xinput::check_; // ƒNƒ‰ƒX•Ï”’è‹`