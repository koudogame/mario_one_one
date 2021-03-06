#pragma once 
#include "item_base.hpp"

class Powerup :
    public ItemBase
{
public :
    const int kSpeed    = 4;     // キノコ進む速さ
    const int kPunchUp  = 16;    // 叩かれて上に上がる
    const int kNoBlock  = 115;   // 何もないアイテムのID
    const int kGround   = 575;   // 床の最低ライン

    Powerup( Field* field ) : ItemBase( field ) {};
    void update( int Screenover) override;
    void flagChange( int Status )override;

    int getPosX() override;
    int getPosY() override;
    void posCollision() override;   // マリオと当たったとき

    void flowerAnimation();         // キラキラさせるアニメーション

private : 
    int up_cnt_     = 0;
    int direction_  = 1;
    bool up_flag_   = true;
    bool punch_     = true;
    bool turn_      = true;

    int animation_cnt_    = 0;
    int flower_animation_ = 0;
};