#include "share.hpp"
#include "ui_coin.hpp"

void UICoin::initialize()
{
    // �A�C�e���摜�ǂݍ���
    item_texture_ = LoadGraph( "texture/mario_item.png" );

    // �S����
    rect_.right = kQuarterSize;
    rect_.top = 0;
    rect_.bottom = kQuarterSize;
}

void UICoin::update(){}

void UICoin::draw( int Texture )
{
    // �ꌅ��
    DrawRectGraph( kNumPosAX, kUIposY,
        left( number_a_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

    // �񌅖�
    DrawRectGraph( kNumPosBX, kUIposY,
        left( number_b_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

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
    // �P�O�����ƂɌJ��オ��
    number_a_ = Coin % kCountUp;
    number_b_ = Coin / kCountUp;
}
