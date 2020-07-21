#pragma once 
#include "enemy_base.hpp"

class Kuribo :
    public EnemyBase
{
public :
    static const int kKuribo    = 0;        // クリボーID
    static const int kDown      = 5;        // 落ちていく
    static const int kDeathTime = 32;       // 画面から消えるまでのリミット
    static const int kDead      = 112;      // 死んだとき
    static const int kFieldSize = 800;      // 下の限界値

    Kuribo( Field* Field ) : EnemyBase( Field ) {};
    void update( int ScreenOver )override;
    
    int getPosX() override;
    int getPosY() override;

    void posCollision(int Touch) override;  // マリオとの衝突があったとき
    void animation();                       // 歩くアニメーション

private : 
    int death_cnt_       = 0;               // 消えるまでのカウントダウン
    bool move_start_     = true;            // true : 動かない, false : 動き出す
    bool alive_          = true;            // true : 生きている, false : 死んでいる
};