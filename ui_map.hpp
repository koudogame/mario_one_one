#pragma once
#include "ui_base.hpp"
    
/* ���̃N���X����A - B�ƕ\�� */

class UIMap :
    public UIBase
{
public:
    const int kNumPosAX = 840;                         // A�̃|�W�V����
    const int kLineX    = kNumPosAX + kQuarterSize;    // �[�̃|�W�V����
    const int kNumPosBX = kLineX + kQuarterSize;       // B�̃|�W�V����

    void initialize() override;
    void draw(int) override;

private:                      
}; 