#pragma once
#include "item_base.hpp"

class CastleFlag :
    public ItemBase
{
public:
    static const int kFlag = 201;           // 旗のあるべき場所

    CastleFlag( Field* field ) : ItemBase( field ) {};
    void upHata( bool End ) override;       // 旗を掲げる関数

private:
    int up_cnt_ = 0;
};