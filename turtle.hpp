#pragma once
#include "enemy_base.hpp"

class Turtle :
    public EnemyBase
{
public :
    Turtle( Field* Field ) : EnemyBase( Field ) {};

    void update( int ScreenOver )override;

    int getPosX()override;
    int getPosY()override;
    void posCollision() override;   // active_ : trueで踏んだ時
    void shellCollision() override;

    void animation();

private : 
    bool active_ = true;            // true : 起きている, false : 甲羅の中
    bool pushout_ = true;          // true : 止まっている, false : 横に高速移動

    int action_cnt_ = -1;            // 2回とっている前提として
};