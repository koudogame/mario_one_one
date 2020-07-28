#include "share.hpp"
#include "ui_coin.hpp"

void UICoin::initialize()
{
    // アイテム画像読み込み
    item_texture_ = LoadGraph( "texture/mario_item.png" );

    // コイン枚数0に初期化
    number_b_ = 0;

    // 全共通
    rect_.right = kHalfSize;
    rect_.top = 0;
    rect_.bottom = kHalfSize;
}

void UICoin::update(){}

void UICoin::draw( int Texture )
{
    // A
    DrawRectGraph( kNumPosAX, kUIposY,
        left( number_a_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // B
    DrawRectGraph( kNumPosBX, kUIposY,
        left( number_b_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // ×
    DrawRectGraph( kTimes, kUIposY,
        left( kTimesNum ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // コイン
    DrawRectGraph( kCoinPosX, kUIposY - (kHalfSize / 2),
        left( kCoinNum ), Quintuple, rect_.right, kSize,
        item_texture_, TRUE, FALSE );

}

void UICoin::finalize()
{
    // 画像破棄
    DeleteGraph( item_texture_ );
}

void UICoin::coinCounter( int Coin )
{
    number_a_ = Coin % 10;
    number_b_ = Coin / 10;
}
