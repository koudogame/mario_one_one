#pragma once
#include <DxLib.h>
#include <fstream>
#include "block_base.hpp"

enum PartsNum
{
    kRightUp, kLeftUp, kRightDown, kLeftDown, kPartsNum
};

enum Position
{
    kPositionX, kPositionY, kXYPosition
};

class Brick :
    public BlockBase
{
public : 
    static const int kGravity  = 1;     // �d��
    static const int kSpeed    = 3;     // ����
    static const int kSize     = 64;    // �u���b�N�T�C�Y
    static const int kJumpUp   = 20;    // ����u���b�N���ˏ�
    static const int kJumpDown = 10;    // ����u���b�N���ˉ�
    static const int kNoBlock  = 190;   // �����Ȃ��u���b�NID

    void initialize( const int Id, const RECT Rect, const int X, const int Y) override;
    void update(int) override;
    void draw( int, int ) override;
    void downBlock() override;

    void standby(int, int) override;    // �҂��Ă���Ƃ��̍��W

private:
    int acceleration_up_;
    int acceleration_down_;
    int pos_x_;
    int pos_y_;

    bool punch_;

    int break_parts_[ kPartsNum ][ kXYPosition ] = { 0 };
};