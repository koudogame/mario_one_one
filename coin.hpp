#pragma once
#include "item_base.hpp"

class Coin :
    public ItemBase
{
public :
    static const int kChangeSpeed = 3;
    static const int kJumpPower   = 15;
    static const int kSize        = 64;
    static const int kCoin        = 80;
    static const int kNoBlock     = 115;

    Coin( Field* field ) : ItemBase( field ) {};
    void update(int Screenover) override;
    void flagChange(int Status) override;   // ŠÖ”‚Ìˆ—‚ğˆê“x‚É§ŒÀ‚·‚é‚½‚ß

private : 
    bool punch_ = true;

    int animation_cnt_ = 0;
    int coin_animation_ = 0;
};