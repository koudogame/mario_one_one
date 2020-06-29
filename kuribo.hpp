#pragma once 
#include "enemy_base.hpp"

class Kuribo :
    public EnemyBase
{
public :
    static const int kKuribo    = 0;
    static const int kSpeed     = 2;
    static const int kDeathTime = 32;
    static const int kDead      = 112;
    static const int kNoBlock   = 119;
    static const int kGround    = 575;

    Kuribo( Field* Field ) : EnemyBase( Field ) {};
    void update( int ScreenOver )override;
    
    int getPosX() override;
    int getPosY() override;
    void posCollision() override;

    void animation();

private : 
    int animation_       = 0;
    int walk_animation_  = -1;              // -1 : 左足, 　　1 : 右足
    int direction_       = -1;              // -1 : 左へ進む, 1 : 右へ進む 
    int death_cnt_       = 0;               // 消えるまでのカウントダウン
    bool move_start_     = true;            // true : 動かない, false : 動き出す
    bool alive_          = true;            // true : 生きている, false : 死んでいる
};