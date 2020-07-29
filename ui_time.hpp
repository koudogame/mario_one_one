#pragma once
#include "ui_base.hpp"

class UITime :
    public UIBase
{
public :
    const int kSecond       = 20;       // ��b�����炷�t���[����
    const int kDefaultTimer = 400;      // ��������
    const int kNumPosCX     = 1100;
    const int kNumPosBX     = kNumPosCX + kQuarterSize;
    const int kNumPosAX     = kNumPosBX + kQuarterSize;

    void initialize() override;
    void update() override;
    void draw(int) override;

private :
    int clock_cnt_; // ���ԊǗ�
    int timer_;     // ���ԃZ�b�g
    int number_c_;  // �O����
};