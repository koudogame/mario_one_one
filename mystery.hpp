#pragma once
#include "block_base.hpp"

class Mystery :
    public BlockBase
{
public :
    void update(int Status) override;   // �@���ꂽ�Ƃ�
    void downBlock() override;          // �u���b�N�������Ȃ����Ƃ�
};