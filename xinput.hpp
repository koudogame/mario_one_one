#pragma once 

// キー状態
enum Check
{
    kNothing = 0, kPress = 1, kHold = 2
};

class Xinput
{
public:
    // ボタンの状態が返ってくる関数
    static int XInput( uint32_t Button );

private:
    static int check_;
};