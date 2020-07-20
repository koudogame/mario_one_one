#pragma once
#include "enemy_base.hpp"

class Turtle :
    public EnemyBase
{
public:
    static const int kFieldSize = 780;

    Turtle( Field* Field ) : EnemyBase( Field ) {};

    void update( int ScreenOver )override;

    int getPosX()override;
    int getPosY()override;
    void posCollision( int Touch ) override; // active_ : trueで踏んだ時
    void shellCollision() override;          // 甲羅状態で当たったとき
    void fireCollision() override;           // ファイアと当たったとき

    void animation();                        // 歩くアニメーション

    inline bool getPushFlag()override { return pushout_; }

private:
    bool active_ = true;                     // true : 起きている, false : 甲羅の中
    bool pushout_ = true;                    // true : 止まっている, false : 横に高速移動

    int action_cnt_ = -1;                    // 2回とっている前提として
};