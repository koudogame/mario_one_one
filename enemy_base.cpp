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
        // RECT�w�肵�ĕ`����s���֐�
        DrawRectGraph(
            texture_position_x, texture_position_y,                                 // �`��ʒu
            (int&)enemy_parts_.rect.left, (int&)enemy_parts_.rect.top,              // �؂��荶��
            (int&)enemy_parts_.rect.right, (int&)enemy_parts_.rect.bottom,          // �؂���E��
            Texture, TRUE, FALSE );                                                 // �e�N�X�`���l�[���A�����x�A���]
    }
    else {
        // RECT�w�肵�ĕ`����s���֐�
        DrawRectGraph(
            texture_position_x, texture_position_y - (kSize / 2),                   // �`��ʒu
            (int&)enemy_parts_.rect.left, (int&)enemy_parts_.rect.top,              // �؂��荶��
            (int&)enemy_parts_.rect.right, (int&)enemy_parts_.rect.bottom,          // �؂���E��
            Texture, TRUE, FALSE );                                                 // �e�N�X�`���l�[���A�����x�A���]
    }
}

bool EnemyBase::getPushFlag()
{
    // Override�Œl��Ԃ�
    return true;
}

int EnemyBase::getPosX()
{
    // ���ꂼ���Override���Ēl��n��
    return 0;
}

int EnemyBase::getPosY()
{
    // ���ꂼ���Override���Ēl��n��
    return 0;
}

void EnemyBase::posCollision(int Touch){}

void EnemyBase::shellCollision(){}