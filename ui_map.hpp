#pragma once
#include "ui_base.hpp"
    
/* このクラス内はA - Bと表す */

class UIMap :
    public UIBase
{
public:
    const int kNumPosAX = 720;    // Aのポジション
    const int kNumPosBX = 804;    // Bのポジション
    const int kLineX    = 762;    // ーのポジション

    void initialize() override;
    void draw(int) override;

private:                      
}; 