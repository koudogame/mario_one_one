#include "enemy_base.hpp"

void EnemyBase::initialize( const int Id, const RECT Rect, const int X, const int Y )
{
    enemy_parts_.Id = Id;
    enemy_parts_.rect = Rect;
    enemy_parts_.x = X;
    enemy_parts_.y = Y;
}

void EnemyBase::update( int ScreenOver )
{
}

void EnemyBase::draw( int Texture, int ScreenOver )
{
    int texture_position_x = enemy_parts_.x - ScreenOver;
    int texture_position_y = enemy_parts_.y;

    if( enemy_parts_.rect.bottom == kSize )
    {
        // RECT指定して描画を行う関数
        DrawRectGraph(
            texture_position_x, texture_position_y,                                 // 描画位置
            (int&)enemy_parts_.rect.left, (int&)enemy_parts_.rect.top,              // 切り取り左上
            (int&)enemy_parts_.rect.right, (int&)enemy_parts_.rect.bottom,          // 切り取り右下
            Texture, TRUE, FALSE );                                                 // テクスチャネーム、透明度、反転
    }
    else {
        // RECT指定して描画を行う関数
        DrawRectGraph(
            texture_position_x, texture_position_y - (kSize / 2),                   // 描画位置
            (int&)enemy_parts_.rect.left, (int&)enemy_parts_.rect.top,              // 切り取り左上
            (int&)enemy_parts_.rect.right, (int&)enemy_parts_.rect.bottom,          // 切り取り右下
            Texture, TRUE, FALSE );                                                 // テクスチャネーム、透明度、反転
    }
}

bool EnemyBase::getPushFlag()
{
    // Overrideで値を返す
    return true;
}

int EnemyBase::getPosX()
{
    // それぞれでOverrideして値を渡す
    return 0;
}

int EnemyBase::getPosY()
{
    // それぞれでOverrideして値を渡す
    return 0;
}

void EnemyBase::posCollision(int Touch){}

void EnemyBase::shellCollision(){}