#include "ui_time.hpp"

void UITime::initialize()
{
    number_c_ = 0;              // 三桁目初期化
    clock_cnt_ = 0;             // カウント初期化
    timer_ = kDefaultTimer;     // timerセット

    // 全共通
    rect_.right = kQuarterSize;
    rect_.top = 0;
    rect_.bottom = kQuarterSize;
}

void UITime::update()
{    
    clock_cnt_++;               // 時間管理

    if( clock_cnt_ == kSecond )
    {
        clock_cnt_ = 0;         // カウントリセット
        timer_--;               // 時間を減らす
    }

    // 制限時間計算    
    number_c_ = timer_ / 100;           // 三桁目
    number_b_ = (timer_ % 100) / 10;    // 二桁目
    number_a_ = timer_ % 10;            // 一桁目
}

void UITime::draw(int Texture)
{
    // 一桁目
    DrawRectGraph( kNumPosAX, kUIposY,
        left( number_a_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
    
    // 二桁目
    DrawRectGraph( kNumPosBX, kUIposY,
        left( number_b_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
    
    // 三桁目
    DrawRectGraph( kNumPosCX, kUIposY,
        left( number_c_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

}
