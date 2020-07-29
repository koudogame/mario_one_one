#pragma once
#include "ui_base.hpp"
    
/* このクラス内はA - Bと表す */

class UIMap :
    public UIBase
{
public:
    const int kDigitArray = 2;
    const int kStartPos = 840;                         // Aのポジション
    const int kLineX = kStartPos + kQuarterSize;    // ーのポジション

    void initialize() override;
    void draw( int ) override;

private:
    int map_num_;
};