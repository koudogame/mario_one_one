#include "share.hpp"
#include "ui_map.hpp"

void UIMap::initialize()
{      
    // �}�b�v1-1
    map_num_ = 11;

    // �e�l�̕��܂ŃV�t�g
    auto binary = 0b10;
    for( int i = 0; i < kDigitArray; i++ )
    {
        digit_[ i ] = digit( map_num_, binary >> i );
    }
}        

void UIMap::draw(int Texture )
{
    // �e���̕`��
    for( int i = 0; i < kDigitArray; i++ )
    {
        DrawRectGraph( kStartPos + (i * kHalfSize), kUIposY,
            left( digit_[i] ), rect_.top, rect_.right, rect_.bottom,
            Texture, TRUE, FALSE );
    }
    
    // -
    DrawRectGraph( kLineX, kUIposY,
        kTripleSize - kQuarterSize, rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
}