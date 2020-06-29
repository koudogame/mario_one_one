#pragma once
#include "block_base.hpp"

class Brick :
    public BlockBase
{
public : 
    void update(int Status) override;
    void downBlock() override;
};