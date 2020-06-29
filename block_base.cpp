#include "block_base.hpp"

bool BlockBase::initialize(const int Id, const RECT Rect, const int X, const int Y)
{
    parts_.Id = Id;
    parts_.rect = Rect;
    parts_.x = X;
    parts_.y = Y;

    upblock_flag_ = true;

    return true;
}

void BlockBase::update(int Status){}

void BlockBase::draw( int Texture, const int ScreenOver )
{
    int texture_position_x = parts_.x - ScreenOver;
    int texture_position_y = parts_.y;

    // RECT�w�肵�ĕ`����s���֐�
    DrawRectGraph(
        texture_position_x, texture_position_y,                                 // �`��ʒu
        (int&)parts_.rect.left, (int&)parts_.rect.top,                          // �؂��荶��
        (int&)parts_.rect.right, (int&)parts_.rect.bottom,                      // �؂���E��
        Texture, TRUE, FALSE );                                                 // �e�N�X�`���l�[���A�����x�A���]
}

void BlockBase::downBlock(){}