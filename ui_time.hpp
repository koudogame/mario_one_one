#pragma once
#include "ui_base.hpp"

class UITime :
    public UIBase
{
public :
    const int kDigitArray   = 3;        // ���ԕ`��R���܂őΉ�
    const int kSecond       = 20;       // ��b�����炷�t���[����
    const int kDefaultTimer = 400;      // ��������
    const int kStartPos     = 1100;     // �x�[�X���W

    void initialize() override;
    void update() override;
    void draw(int) override;

    void setTime(int);
    void setGoalFlag(bool);

    inline int getTime() { return timer_; }
    inline bool timeLimit() { return time_limit_; }

private :
    int clock_cnt_;   // ���ԊǗ�
    int timer_;       // ���ԃZ�b�g

    bool goal_flag_;  // true : Goal�O, false : Goal��
    bool time_limit_; // true : ���ԓ�, false : ���ԊO
};