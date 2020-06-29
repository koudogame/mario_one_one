#pragma once
#include "block_base.hpp"

class Mystery :
    public BlockBase
{
public :
    void update(int Status) override;   // ’@‚©‚ê‚½‚Æ‚«
    void downBlock() override;          // ƒuƒƒbƒN‚ª‚‚­‚È‚Á‚½‚Æ‚«
};