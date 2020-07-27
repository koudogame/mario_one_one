#pragma once
#include <windows.h>
#include <DxLib.h>

// �p�[�c�\����
struct Parts
{
    int Id;                     // ID�ԍ��̎擾
    RECT rect;                  // �؂���͈�
    int x, y;                   // �|�W�V����

    // ������
    Parts()
    {
        Id = 0;
        rect = { 0L };
        x = 0, y = 0;
    }
};

class BlockBase
{
protected:
    //Parts�\���̂��Ăяo��
    Parts parts_;
    int base_pos_;
    bool upblock_flag_;          // true : �@����ĂȂ�, false : �@���ꂽ
    bool stand_by_;              // true : ������, false : �����o��

public :
    virtual void initialize(const int Id, const RECT Rect, const int X, const int Y);
    virtual void update(int);
    virtual void draw( int Texture, const int ScreenOver );
    
    virtual void downBlock();          // �̂��������Ƃ��Ƀu���b�N���グ��������֐�
    virtual void standby(int,int);     // �@���ꂽ�Ƃ���false�֕ς���֐�

    inline const int getId() {return parts_.Id; }
    inline const int getPositionX() { return parts_.x; }
    inline const int getPositionY() { return parts_.y; }
    inline void setPosition(const int& X, const int& Y) { parts_.x = X, parts_.y = Y; }
};