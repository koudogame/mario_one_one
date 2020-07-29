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

    void setGoalFlag(bool);

    inline bool timeLimit() { return time_limit_; }

private :
    int clock_cnt_;   // ���ԊǗ�
    int timer_;       // ���ԃZ�b�g
    int number_c_;    // �O����

    bool goal_flag_;  // true : Goal�O, false : Goal��
    bool time_limit_; // true : ���ԓ�, false : ���ԊO
};