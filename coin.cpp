#include "coin.hpp"

void Coin::update()
{
    if( up_ == false ) 
        item_.y -= 1;
}

void Coin::flagChange( int Status )
{
    status_ = Status;
    up_ = false;
}
