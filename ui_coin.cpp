#include "share.hpp"
#include "ui_coin.hpp"

void UICoin::initialize()
{
    // �A�C�e���摜�ǂݍ���
    item_texture_ = LoadGraph( "texture/mario_item.png" );

    // �R�C������0�ɏ�����
    number_b_ = 0;

    // �S����
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

    // �~
    DrawRectGraph( kTimes, kUIposY,
        left( kTimesNum ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // �R�C��
    DrawRectGraph( kCoinPosX, kUIposY - (kHalfSize / 2),
        left( kCoinNum ), Quintuple, rect_.right, kSize,
        item_texture_, TRUE, FALSE );

}

void UICoin::finalize()
{
    // �摜�j��
    DeleteGraph( item_texture_ );
}

void UICoin::coinCounter( int Coin )
{
    number_a_ = Coin % 10;
    number_b_ = Coin / 10;
}
