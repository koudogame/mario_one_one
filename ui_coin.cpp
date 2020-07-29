#include "ui_coin.hpp"

void UICoin::initialize()
{
    // �A�C�e���摜�ǂݍ���
    item_texture_ = LoadGraph( "texture/mario_item.png" );
}

void UICoin::update(){}

void UICoin::draw( int Texture )
{
    for( int i = 0; i < kDigitArray; i++ )
    {
        DrawRectGraph( kStartPos + (i * kQuarterSize), kUIposY,
            left( digit_[i] ), rect_.top, rect_.right, rect_.bottom,
            Texture, TRUE, FALSE );
    }

    // �~
    DrawRectGraph( kTimes, kUIposY,
        left( kTimesNum ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // �R�C��
    DrawRectGraph( kCoinPosX, kUIposY - kHalfSize,
        kSize, Quintuple, kHalfSize, kSize,
        item_texture_, TRUE, FALSE );

}

void UICoin::finalize()
{
    // �摜�j��
    DeleteGraph( item_texture_ );
}

void UICoin::coinCounter( int Coin )
{
    // �e�l�̕��܂ŃV�t�g
    auto binary = 0b10;
    for( int i = 0; i < kDigitArray; i++ )
    {
        digit_[ i ] = digit( Coin, binary >> i );
    }
}