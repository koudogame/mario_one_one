#pragma once
#include "item_base.hpp"

class Coin :
    public ItemBase
{
public :
    static const int kJumpPower = 20;
    static const int kSize      = 64;
    static const int kNoBlock   = 115;

    Coin( Field* field ) : ItemBase( field ) {};
    void update() override;
    void flagChange(int Status) override;
};