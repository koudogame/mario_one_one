#pragma once
#include "ui_base.hpp"

/* 一桁目 A, 二桁目 Bと表す */

class UICoin :
    public UIBase
{
public:
    const int kCoinNum  = 2;      // コインの左端
    const int kTimesNum = 10;     // ×の番号 
    const int kCountUp  = 10;     // カウントアップ
    const int kCoinPosX = 434;    // コインのポジション
    const int kTimes    = 492;    // ×のポジション 
    const int kNumPosBX = 534;    // Bのポジション
    const int kNumPosAX = 576;    // Aのポジション

    void initialize() override;
    void update() override;
    void draw(int) override;
    void finalize() override;

    void coinCounter( int );      // 叩かれた分だけ取得

private:
    int item_texture_;            // アイテムテクスチャ
};