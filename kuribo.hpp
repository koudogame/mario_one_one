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
    int walk_animation_  = -1;              // -1 : ����, �@�@1 : �E��
    int direction_       = -1;              // -1 : ���֐i��, 1 : �E�֐i�� 
    int death_cnt_       = 0;               // ������܂ł̃J�E���g�_�E��
    bool move_start_     = true;            // true : �����Ȃ�, false : �����o��
    bool alive_          = true;            // true : �����Ă���, false : ����ł���
};