#include "ui_time.hpp"

void UITime::initialize()
{
    time_limit_ = true;             // 時間内外伝達用
    goal_flag_ = true;              // プレイヤーゴール状態

    clock_cnt_ = 0;                 // カウント初期化
    timer_ = kDefaultTimer;         // timerセット
}

void UITime::update()
{
    // 時間制限前 && ゴール前
    if( time_limit_ && goal_flag_ )
    {
        clock_cnt_++;               // 時間管理

        if( clock_cnt_ == kSecond )
        {
            clock_cnt_ = 0;         // カウントリセット

            if( timer_ > 0 )
                timer_--;           // 時間を減らす
            else
                time_limit_ = false;
        }

        // 指定回数分シフト
        auto binary = 0b100;
        for( int i = 0; i < kDigitArray; i++ )
        {
            digit_[ i ] = digit( timer_, binary >> i );
        }
    }
}

void UITime::draw( int Texture )
{
    // 用意された桁まで描画
    for( int i = 0; i < kDigitArray; i++ )
    {
        DrawRectGraph( kStartPos + (i * kQuarterSize), kUIposY,
            left( digit_[ i ] ), rect_.top, rect_.right, rect_.bottom,
            Texture, TRUE, FALSE );
    }
}

void UITime::setGoalFlag(bool GoalFlag)
{
    goal_flag_ = GoalFlag;          // フラグの受け渡し
}

void UITime::setTime( int Time )
{
    timer_ = Time;

    // 指定回数分シフト
    auto binary = 0b100;
    for( int i = 0; i < kDigitArray; i++ )
    {
        digit_[ i ] = digit( timer_, binary >> i );
    }
}
