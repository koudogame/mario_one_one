#pragma once
#include <windows.h>
#include <DxLib.h>

// �p�[�c�\����
struct Parts
{
    int Id;                     // ID�ԍ��̎擾
    RECT rect;             // �؂���͈�
    int x, y;                 // �|�W�V����

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

public :
    virtual bool initialize(const int Id, const RECT Rect, const int X, const int Y);
    virtual void update();
    virtual void draw( int Texture, const int ScreenOver );

    inline const int getId() {return parts_.Id; }
    inline const int getPositionX() { return parts_.x; }
    inline const int getPositionY() { return parts_.y; }
    inline void setPosition(const int& X, const int& Y) { parts_.x = X, parts_.y = Y; }
};