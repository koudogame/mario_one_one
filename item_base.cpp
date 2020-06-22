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

    // RECT指定して描画を行う関数
    DrawRectGraph(
        texture_position_x, texture_position_y,                                 // 描画位置
        (int&)item_.rect.left, (int&)item_.rect.top,                          // 切り取り左上
        (int&)item_.rect.right, (int&)item_.rect.bottom,                      // 切り取り右下
        Texture, TRUE, FALSE );                                                 // テクスチャネーム、透明度、反転
}

void ItemBase::flagChange( int Status )
{
}
