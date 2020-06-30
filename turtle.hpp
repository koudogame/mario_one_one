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
    void posCollision() override;   // active_ : true‚Å“¥‚ñ‚¾
    void shellCollision() override;

    void animation();

private : 
    bool active_ = true;            // true : ‹N‚«‚Ä‚¢‚é, false : b—…‚Ì’†
    bool pushout_ = true;          // true : ~‚Ü‚Á‚Ä‚¢‚é, false : ‰¡‚É‚‘¬ˆÚ“®

    int action_cnt_ = -1;            // 2‰ñ‚Æ‚Á‚Ä‚¢‚é‘O’ñ‚Æ‚µ‚Ä
};