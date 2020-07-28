#pragma once
#include "ui_base.hpp"

/* �ꌅ�� A, �񌅖� B�ƕ\�� */

class UICoin :
    public UIBase
{
public:
    const int kNumPosAX = 598;    // A�̃|�W�V����
    const int kNumPosBX = 556;    // B�̃|�W�V����
    const int kTimes    = 514;    // �~�̃|�W�V���� 
    const int kCoinPosX = 472;    // �R�C���̃|�W�V����
    const int kCountUp  = 10;     // �J�E���g�A�b�v
    const int kTimesNum = 10;     // �~�̔ԍ� 
    const int kCoinNum  = 2;      // �R�C���̍��[

    void initialize() override;
    void update() override;
    void draw(int) override;
    void finalize() override;

    void coinCounter( int );

private:
    int item_texture_;
};