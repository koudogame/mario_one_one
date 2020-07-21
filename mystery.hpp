#pragma once
#include "block_base.hpp"

class Mystery :
    public BlockBase
{
public :
    static const int kChangeTime = 8;   // はてなボックスアニメーション用

    void update(int) override;          // 叩かれたときの処理
    void downBlock() override;          // ブロックが高くなったとき
    void standby(int, int) override;    // 叩かれたときにfalseへ変更する関数

private : 
    int animation_cnt_ = 0;             // アニメーション用
};