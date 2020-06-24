#pragma once 
#include "item_base.hpp"

class Powerup :
    public ItemBase
{
public :
    static const int kMashroom = 0;
    static const int kSpeed    = 4;
    static const int kFlower   = 16;
    static const int kSize     = 64;
    static const int kNoBlock  = 115;
    static const int kGround   = 575;

    Powerup( Field* field ) : ItemBase( field ) {};
    void update(int Screenover) override;
    void flagChange( int Status )override;

private : 
    int up_cnt_     = 0;
    int direction_  = 1;
    bool up_flag_   = true;
    bool punch_     = true;
};