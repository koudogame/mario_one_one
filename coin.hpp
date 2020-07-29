#pragma once
#include "item_base.hpp"

class Coin :
    public ItemBase
{
public :
    const int kChangeSpeed = 3;               // �R�C���A�j���[�V�����p
    const int kReset       = 3;               // �R�C���A�j���[�V�����p
    const int kJumpPower   = 15;              // �R�C���@�������̃W�����v��
    const int kNoBlock     = 115;             // �����Ȃ�ID

    Coin( Field* field ) : ItemBase( field ) {};
    void update(int Screenover) override;
    void flagChange(int Status) override;     // �֐��̏�������x�ɐ������邽��

    bool getPunch() override;                 // �R�C����@�������擾�ł���

private : 
    bool punch_ = true;

    int animation_cnt_ = 0;
    int coin_animation_ = 0;
};