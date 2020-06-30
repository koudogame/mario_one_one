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
    void posCollision() override;   // active_ : true�œ��񂾎�
    void shellCollision() override;

    void animation();

private : 
    bool active_ = true;            // true : �N���Ă���, false : �b���̒�
    bool pushout_ = true;          // true : �~�܂��Ă���, false : ���ɍ����ړ�

    int action_cnt_ = -1;            // 2��Ƃ��Ă���O��Ƃ���
};