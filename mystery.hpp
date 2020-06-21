#pragma once
#include "block_base.hpp"

class Mystery :
    public BlockBase
{
public :
    void update(int Status) override;
};