#pragma once
#include <DxLib.h>
#include <fstream>
#include "release.hpp"

enum Head
{
    kRHead, kLHead, kRLHead
};

enum PartsNum
{
    kRightUp, kLeftUp, kRightDown, kLeftDown, kPartsNum
};

enum Position
{
    kPositionX, kPositionY, kXYPosition
};

class BreakBlock
{
public:
    static const int kGravity = 1;
    static const int kSpeed = 3;
    static const int kSize = 64;
    static const int kJumpUp = 25;
    static const int kJumpDown = 15;

    void  initialize();
    void update(int, int, int, int);
    void draw(int);
    void finalize();

private:
    int texture_;
    int acceleration_up_;
    int acceleration_down_;

    bool punch_;
    bool right_head_;
    bool left_head_;

    int break_parts_[kRLHead][kPartsNum][kXYPosition];
};

