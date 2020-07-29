#pragma once
#include "ui_base.hpp"
    
/* このクラス内はA - Bと表す */

class UIMap :
    public UIBase
{
public:
    const int kNumPosAX = 840;                         // Aのポジション
    const int kLineX    = kNumPosAX + kQuarterSize;    // ーのポジション
    const int kNumPosBX = kLineX + kQuarterSize;       // Bのポジション

    void initialize() override;
    void draw(int) override;

private:                      
}; 