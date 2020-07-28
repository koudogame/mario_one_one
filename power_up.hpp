#pragma once 
#include "item_base.hpp"

class Powerup :
    public ItemBase
{
public :
    const int kSpeed    = 4;     // �L�m�R�i�ޑ���
    const int kPunchUp  = 16;    // �@����ď�ɏオ��
    const int kNoBlock  = 115;   // �����Ȃ��A�C�e����ID
    const int kGround   = 575;   // ���̍Œ჉�C��

    Powerup( Field* field ) : ItemBase( field ) {};
    void update( int Screenover) override;
    void flagChange( int Status )override;

    int getPosX() override;
    int getPosY() override;
    void posCollision() override;   // �}���I�Ɠ��������Ƃ�

    void flowerAnimation();         // �L���L��������A�j���[�V����

private : 
    int up_cnt_     = 0;
    int direction_  = 1;
    bool up_flag_   = true;
    bool punch_     = true;
    bool turn_      = true;

    int animation_cnt_    = 0;
    int flower_animation_ = 0;
};