#include "share.hpp"
#include "ui_score.hpp"

void UIScore::initialize()
{
    score_ = 0;     // �X�R�A�̏�����
    timer_ = 0;     // �^�C���̏�����
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

void UIScore::changeTime( int Time )
{
    timer_ = Time;        // ���Ԃ�ۑ�
    timer_--;             // �P�b���炷

    score_ += kTimeScore; // �X�R�A��50�ǉ�
    
    // �e�l�̕��܂ŃV�t�g
    auto binary = 0b100000;
    for( int i = 0; i < kDigitArray; i++ )
    {
        digit_[ i ] = digit( score_, binary >> i );
    }
}
