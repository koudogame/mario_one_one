#pragma once
#include "block_base.hpp"

class Mystery :
    public BlockBase
{
public :
    const int kDownSpeed  = 2;          // ブロックが下に落ちる
    const int kChangeTime = 8;          // はてなボックスアニメーション用
    const int kBlockUp    = 16;         // 叩かれたときに上に上がる

    void update(int) override;          // 叩かれたときの処理
    void downBlock() override;          // ブロックが高くなったとき
    void standby(int, int) override;    // 叩かれたときにfalseへ変更する関数

private : 
    int animation_cnt_ = 0;             // アニメーション用
};