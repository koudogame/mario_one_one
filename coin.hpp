#pragma once
#include "item_base.hpp"

class Coin :
    public ItemBase
{
public :
    void update() override;
    void flagChange(int Status) override;
};