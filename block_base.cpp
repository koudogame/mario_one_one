#include "block_base.hpp"

// �u���b�N�S�̂̏�����
void BlockBase::initialize(const int Id, const RECT Rect, const int X, const int Y)
{
    parts_.Id = Id;
    parts_.rect = Rect;
    parts_.x = X;
    parts_.y = Y;

    stand_by_ = true;
    upblock_flag_ = true;
}

// ���ꂼ��ōX�V���Ă��炤
void BlockBase::update(int Status){}

// �u���b�N�̃x�[�X�ƂȂ�`��
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

// �}���I�̑̂Œ@�������Ƀu���b�N���グ��������֐�
void BlockBase::downBlock(){}

// �@���ꂽ�Ƃ�false�ɂ���֐�
void BlockBase::standby(int x, int y){}