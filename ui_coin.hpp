#pragma once
#include "ui_base.hpp"

/* 一桁目 A, 二桁目 Bと表す */

class UICoin :
    public UIBase
{
public:
    const int kCoinNum  = 2;                                 // コインの左端
    const int kTimesNum = 10;                                // ×の番号 
    const int kCountUp  = 10;                                // カウントアップ
    const int kNumPosAX = 424;                               // Aのポジション
    const int kNumPosBX = kNumPosAX - kQuarterSize;          // Bのポジション
    const int kTimes    = kNumPosBX - kQuarterSize;          // ×のポジション 
    const int kCoinPosX = kTimes - kHalfSize - kQuarterSize; // コインのポジション

    void initialize() override;
    void update() override;
    void draw(int) override;
    void finalize() override;

    void coinCounter( int ); // 叩かれた分だけ取得

private:
    int item_texture_;       // アイテムテクスチャ
};