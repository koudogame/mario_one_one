#pragma once
#include "ui_base.hpp"
    
/* ���̃N���X����A - B�ƕ\�� */

class UIMap :
    public UIBase
{
public:
    const int kNumPosAX = 720;    // A�̃|�W�V����
    const int kNumPosBX = 804;    // B�̃|�W�V����
    const int kLineX    = 762;    // �[�̃|�W�V����

    void initialize() override;
    void draw(int) override;

private:                      
}; 