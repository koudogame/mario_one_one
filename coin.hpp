#pragma once
#include "item_base.hpp"

class Coin :
    public ItemBase
{
public :
    static const int kChangeSpeed = 3;      // �R�C���A�j���[�V�����p
    static const int kJumpPower   = 15;     // �R�C���@�������̃W�����v��
    static const int kCoin        = 80;     // �R�C����ID
    static const int kNoBlock     = 115;    // �����Ȃ�ID

    Coin( Field* field ) : ItemBase( field ) {};
    void update(int Screenover) override;
    void flagChange(int Status) override;   // �֐��̏�������x�ɐ������邽��

private : 
    bool punch_ = true;

    int animation_cnt_ = 0;
    int coin_animation_ = 0;
};