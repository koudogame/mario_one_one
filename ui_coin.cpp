#include "ui_coin.hpp"

void UICoin::initialize()
{
    // アイテム画像読み込み
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

    // ×
    DrawRectGraph( kTimes, kUIposY,
        left( kTimesNum ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // コイン
    DrawRectGraph( kCoinPosX, kUIposY - kHalfSize,
        kSize, Quintuple, kHalfSize, kSize,
        item_texture_, TRUE, FALSE );

}

void UICoin::finalize()
{
    // 画像破棄
    DeleteGraph( item_texture_ );
}

void UICoin::coinCounter( int Coin )
{
    // 各値の分までシフト
    auto binary = 0b10;
    for( int i = 0; i < kDigitArray; i++ )
    {
        digit_[ i ] = digit( Coin, binary >> i );
    }
}