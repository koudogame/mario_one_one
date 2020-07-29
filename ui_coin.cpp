#include "share.hpp"
#include "ui_coin.hpp"

void UICoin::initialize()
{
    // ƒAƒCƒeƒ€‰æ‘œ“Ç‚İ‚İ
    item_texture_ = LoadGraph( "texture/mario_item.png" );

    // ‘S‹¤’Ê
    rect_.right = kQuarterSize;
    rect_.top = 0;
    rect_.bottom = kQuarterSize;
}

void UICoin::update(){}

void UICoin::draw( int Texture )
{
    // ˆêŒ…–Ú
    DrawRectGraph( kNumPosAX, kUIposY,
        left( number_a_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // “ñŒ…–Ú
    DrawRectGraph( kNumPosBX, kUIposY,
        left( number_b_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // ~
    DrawRectGraph( kTimes, kUIposY,
        left( kTimesNum ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // ƒRƒCƒ“
    DrawRectGraph( kCoinPosX, kUIposY - kHalfSize,
        kSize, Quintuple, kHalfSize, kSize,
        item_texture_, TRUE, FALSE );

}

void UICoin::finalize()
{
    // ‰æ‘œ”jŠü
    DeleteGraph( item_texture_ );
}

void UICoin::coinCounter( int Coin )
{
    // ‚P‚O–‡‚²‚Æ‚ÉŒJ‚èã‚ª‚è
    number_a_ = Coin % kCountUp;
    number_b_ = Coin / kCountUp;
}
