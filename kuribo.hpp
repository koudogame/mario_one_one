#pragma once 
#include "enemy_base.hpp"

class Kuribo :
    public EnemyBase
{
public :
    static const int kKuribo    = 0;
    static const int kDown      = 5;
    static const int kDeathTime = 32;
    static const int kDead      = 112;

    Kuribo( Field* Field ) : EnemyBase( Field ) {};
    void update( int ScreenOver )override;
    
    int getPosX() override;
    int getPosY() override;
    void posCollision(int Touch) override;

    void animation();

private : 
    int death_cnt_       = 0;               // 消えるまでのカウントダウン
    bool move_start_     = true;            // true : 動かない, false : 動き出す
    bool alive_          = true;            // true : 生きている, false : 死んでいる
};