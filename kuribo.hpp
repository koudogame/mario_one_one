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
    int death_cnt_       = 0;               // ������܂ł̃J�E���g�_�E��
    bool move_start_     = true;            // true : �����Ȃ�, false : �����o��
    bool alive_          = true;            // true : �����Ă���, false : ����ł���
};