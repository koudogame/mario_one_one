#pragma once
#include "item_base.hpp"

class CastleFlag :
    public ItemBase
{
public:
    static const int kFlag = 201;           // Šø‚Ì‚ ‚é‚×‚«êŠ

    CastleFlag( Field* field ) : ItemBase( field ) {};
    void upHata( bool End ) override;       // Šø‚ğŒf‚°‚éŠÖ”

private:
    int up_cnt_ = 0;
};