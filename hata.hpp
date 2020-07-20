#pragma once
#include "item_base.hpp"

class Hata :
    public ItemBase
{
public :
    static const int kHata = 201;

    Hata( Field* field ) : ItemBase( field ) {};
    void upHata( bool End ) override;       // Šø‚ğŒf‚°‚éŠÖ”

private :
    int up_cnt_ = 0;
};