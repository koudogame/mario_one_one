#pragma once
#include "item_base.hpp"

class CastleFlag :
    public ItemBase
{
public:
    const int kDownSpeed = 2;  // ���̗����X�s�[�h      
    const int kFlag = 201;     // ���̂���ׂ��ꏊ

    CastleFlag( Field* field ) : ItemBase( field ) {};
    void upHata( bool End ) override;       // �����f����֐�

private:
    int up_cnt_ = 0;
};