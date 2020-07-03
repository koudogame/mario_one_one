#pragma once
#include "block_base.hpp"

class Mystery :
    public BlockBase
{
public :
    static const int kChangeTime = 8;

    void update(int) override;   // 叩かれたとき
    void downBlock() override;          // ブロックが高くなったとき
    void standby(int, int) override;

private : 
    int animation_cnt_ = 0;         // アニメーション用
};