#pragma once
#include "ui_base.hpp"

class UITime :
    public UIBase
{
public :
    const int kDigitArray   = 3;        // 時間描画３桁まで対応
    const int kSecond       = 20;       // 一秒を減らすフレーム数
    const int kDefaultTimer = 400;      // 制限時間
    const int kStartPos     = 1100;     // ベース座標

    void initialize() override;
    void update() override;
    void draw(int) override;

    void setTime(int);
    void setGoalFlag(bool);

    inline int getTime() { return timer_; }
    inline bool timeLimit() { return time_limit_; }

private :
    int clock_cnt_;   // 時間管理
    int timer_;       // 時間セット

    bool goal_flag_;  // true : Goal前, false : Goal後
    bool time_limit_; // true : 時間内, false : 時間外
};