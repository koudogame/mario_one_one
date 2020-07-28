#pragma once
#include "block_base.hpp"

class Mystery :
    public BlockBase
{
public :
    const int kDownSpeed  = 2;          // �u���b�N�����ɗ�����
    const int kChangeTime = 8;          // �͂Ăȃ{�b�N�X�A�j���[�V�����p
    const int kBlockUp    = 16;         // �@���ꂽ�Ƃ��ɏ�ɏオ��

    void update(int) override;          // �@���ꂽ�Ƃ��̏���
    void downBlock() override;          // �u���b�N�������Ȃ����Ƃ�
    void standby(int, int) override;    // �@���ꂽ�Ƃ���false�֕ύX����֐�

private : 
    int animation_cnt_ = 0;             // �A�j���[�V�����p
};