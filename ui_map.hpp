#pragma once
#include "ui_base.hpp"
    
/* ���̃N���X����A - B�ƕ\�� */

class UIMap :
    public UIBase
{
public:
    // A�̃|�W�V����
    const int kNumPosAX = 720;
    const int kNumPosAY = 50;

    // B�̃|�W�V����
    const int kNumPosBX = 804;
    const int kNumPosBY = 50;
    
    // �[�̃|�W�V����
    const int kLineX    = 762;
    const int kLineY    = 50;

    void initialize() override;
    void draw(int) override;

private:         
    Rect<int> rect_; // Rect���g�p
             
    int left_b_;     // B�̍��[
    int number_a_;   // A
    int number_b_;   // B
}; 