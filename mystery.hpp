#pragma once
#include "block_base.hpp"

class Mystery :
    public BlockBase
{
public :
    static const int kChangeTime = 8;

    void update(int) override;   // �@���ꂽ�Ƃ�
    void downBlock() override;          // �u���b�N�������Ȃ����Ƃ�
    void standby(int, int) override;

private : 
    int animation_cnt_ = 0;         // �A�j���[�V�����p
};