#pragma once
#include "ui_base.hpp"

/* 一桁目 A, 二桁目 Bと表す */

class UICoin :
    public UIBase
{
public:
    const int kNumPosAX = 598;    // Aのポジション
    const int kNumPosBX = 556;    // Bのポジション
    const int kTimes    = 514;    // ×のポジション 
    const int kCoinPosX = 472;    // コインのポジション
    const int kCountUp  = 10;     // カウントアップ
    const int kTimesNum = 10;     // ×の番号 
    const int kCoinNum  = 2;      // コインの左端

    void initialize() override;
    void update() override;
    void draw(int) override;
    void finalize() override;

    void coinCounter( int );

private:
    int item_texture_;
};