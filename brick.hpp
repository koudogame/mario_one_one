#pragma once
#include <DxLib.h>
#include <fstream>
#include "block_base.hpp"

class Brick :
    public BlockBase
{
public : 
    const int kSpeed    = 3;     // 速さ
    const int kJumpUp   = 20;    // 壊れるブロック跳ね上
    const int kJumpDown = 10;    // 壊れるブロック跳ね下
    const int kNoBlock  = 190;   // 何もないブロックID

    void initialize( const int Id, const RECT Rect, const int X, const int Y) override;
    void update(int) override;
    void draw( int, int ) override;
    void downBlock() override;

    void standby(int, int) override;    // 待っているときの座標

private:
    int acceleration_up_;
    int acceleration_down_;
    int pos_x_;
    int pos_y_;

    bool punch_;

    int break_parts_[ kBodyParts ][ kPosition ] = { 0 };
};