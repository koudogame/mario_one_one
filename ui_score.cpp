#include "share.hpp"
#include "ui_score.hpp"

void UIScore::initialize()
{
    score_ = 0;     // �X�R�A�̏�����
}

void UIScore::update()
{
    // �e�l�̕��܂ŃV�t�g
    auto binary = 0b100000;
    for( int i = 0; i < kDigitArray; i++ )
    {
        digit_[ i ] = digit( score_, binary >> i );
    }
}

void UIScore::draw( int Texture )
{
    // �e���`��
    for( int i = 0; i < kDigitArray; i++ )
    {
        DrawRectGraph( (kStartPos + (i * kQuarterSize)), kUIposY,
            left( digit_[ i ] ), rect_.top, rect_.right, rect_.bottom,
            Texture, TRUE, FALSE );
    }
}