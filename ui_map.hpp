#pragma once
#include "ui_base.hpp"
    
/* ���̃N���X����A - B�ƕ\�� */

class UIMap :
    public UIBase
{
public:
    const int kDigitArray = 2;
    const int kStartPos = 840;                         // A�̃|�W�V����
    const int kLineX = kStartPos + kQuarterSize;    // �[�̃|�W�V����

    void initialize() override;
    void draw( int ) override;

private:
    int map_num_;
};