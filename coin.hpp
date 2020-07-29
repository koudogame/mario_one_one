#pragma once
#include "item_base.hpp"

class Coin :
    public ItemBase
{
public :
    const int kChangeSpeed = 3;               // コインアニメーション用
    const int kReset       = 3;               // コインアニメーション用
    const int kJumpPower   = 15;              // コイン叩いた時のジャンプ量
    const int kNoBlock     = 115;             // 何もないID

    Coin( Field* field ) : ItemBase( field ) {};
    void update(int Screenover) override;
    void flagChange(int Status) override;     // 関数の処理を一度に制限するため

    bool getPunch() override;                 // コインを叩いたか取得できる

private : 
    bool punch_ = true;

    int animation_cnt_ = 0;
    int coin_animation_ = 0;
};