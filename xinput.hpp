#pragma once 

// キー状態
enum Check
{
    kNothing = 0, kPress = 1, kHold = 2, kRelease = 3
};

class Xinput
{
public:
    // ボタンの状態が返ってくる関数
    static int xinput( uint32_t Button );

private:
    static int bit_;
    static int past_bit_;
};