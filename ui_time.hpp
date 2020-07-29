#pragma once
#include "ui_base.hpp"

class UITime :
    public UIBase
{
public :
    const int kSecond       = 20;       // 一秒を減らすフレーム数
    const int kDefaultTimer = 400;      // 制限時間
    const int kNumPosCX     = 1100;
    const int kNumPosBX     = kNumPosCX + kQuarterSize;
    const int kNumPosAX     = kNumPosBX + kQuarterSize;

    void initialize() override;
    void update() override;
    void draw(int) override;

    void setGoalFlag(bool);

    inline bool timeLimit() { return time_limit_; }

private :
    int clock_cnt_;   // 時間管理
    int timer_;       // 時間セット
    int number_c_;    // 三桁目

    bool goal_flag_;  // true : Goal前, false : Goal後
    bool time_limit_; // true : 時間内, false : 時間外
};