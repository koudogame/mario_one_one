#include "item_base.hpp"

constexpr int kItemBase = 64;

bool ItemBase::initialize( const int Id, const RECT Rect, const int X, const int Y )
{
    item_.Id = Id;
    item_.rect = Rect;
    item_.x = X;
    item_.y = Y;

    up_ = true;

    return true;
}

void ItemBase::update()
{
}

void ItemBase::draw( int Texture, const int Screenover )
{
    int texture_position_x = item_.x - Screenover;
    int texture_position_y = item_.y;

    // RECT�w�肵�ĕ`����s���֐�
    DrawRectGraph(
        texture_position_x, texture_position_y,                                 // �`��ʒu
        (int&)item_.rect.left, (int&)item_.rect.top,                          // �؂��荶��
        (int&)item_.rect.right, (int&)item_.rect.bottom,                      // �؂���E��
        Texture, TRUE, FALSE );                                                 // �e�N�X�`���l�[���A�����x�A���]
}

void ItemBase::flagChange( int Status )
{
}
