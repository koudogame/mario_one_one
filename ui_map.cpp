#include "share.hpp"
#include "ui_map.hpp"

void UIMap::initialize()
{      
    // マップを表示
    number_a_ = 1;
    number_b_ = 1;

    // A
    for( int a = 0; a < number_a_; a++ )
    {
        rect_.left = kHalfSize * number_a_;
    }

    // B
    for( int b = 0; b < number_b_; b++ )
    {
        left_b_ = kHalfSize * number_b_;
    }
    
    // 全共通
    rect_.right = kHalfSize;
    rect_.top = 0;
    rect_.bottom = kHalfSize;
}        

void UIMap::draw(int Texture)
{
    // A
    DrawRectGraph( kNumPosAX, kNumPosAY,
        rect_.left, rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
    
    // B
    DrawRectGraph( kNumPosBX, kNumPosBY,
        left_b_, rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
    
    // -
    DrawRectGraph( kLineX, kLineY,
        Quintuple + kHalfSize, rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
}