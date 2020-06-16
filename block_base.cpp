#include "block_base.hpp"

constexpr int kBlockBase = 64;

bool BlockBase::initialize(const int Id, const RECT Rect, const int X, const int Y)
{
    parts_.Id = Id;
    parts_.rect = Rect;
    parts_.x = X;
    parts_.y = Y;

    return true;
}

void BlockBase::update()
{
    parts_.x -= 1;
}

void BlockBase::draw( int Texture, const int ScreenOver )
{
    int texture_position_x;
    int texture_position_y;

    texture_position_x = parts_.x - ScreenOver;
    texture_position_y = parts_.y;

    // RECT指定して描画を行う関数
    DrawRectGraph(
        texture_position_x, texture_position_y,                            // 描画位置
        (int&)parts_.rect.left, (int&)parts_.rect.top,                      // 切り取り左上
        (int&)parts_.rect.right, (int&)parts_.rect.bottom,              // 切り取り右下
        Texture, TRUE, FALSE );                                                 // テクスチャネーム、透明度、反転
}