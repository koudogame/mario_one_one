#pragma once
#include "ui_base.hpp"
    
/* このクラス内はA - Bと表す */

class UIMap :
    public UIBase
{
public:
    // Aのポジション
    const int kNumPosAX = 720;
    const int kNumPosAY = 50;

    // Bのポジション
    const int kNumPosBX = 804;
    const int kNumPosBY = 50;
    
    // ーのポジション
    const int kLineX    = 762;
    const int kLineY    = 50;

    void initialize() override;
    void draw(int) override;

private:         
    Rect<int> rect_; // Rectを使用
             
    int left_b_;     // Bの左端
    int number_a_;   // A
    int number_b_;   // B
}; 