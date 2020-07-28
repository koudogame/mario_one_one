#include "share.hpp"
#include "ui_map.hpp"

void UIMap::initialize()
{      
    // マップを表示
    number_a_ = 1;
    number_b_ = 1;

    // 全共通
    rect_.right = kHalfSize;
    rect_.top = 0;
    rect_.bottom = kHalfSize;
}        

void UIMap::draw(int Texture )
{
    // A
    DrawRectGraph( kNumPosAX, kUIposY,
        left(number_a_), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
    
    // B
    DrawRectGraph( kNumPosBX, kUIposY,
        left(number_b_), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
    
    // -
    DrawRectGraph( kLineX, kUIposY,
        Quintuple + kHalfSize, rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
}