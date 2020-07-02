#include "break_block.hpp"

void BreakBlock::initialize()
{
    texture_ = LoadGraph("Texture/mario_field.png");

    break_parts_[kRLHead][kPartsNum][kXYPosition] = { 0 };

    punch_ = true;
    right_head_ = true;
    left_head_ = true;
}

void BreakBlock::update(int RightX, int RightY, int LeftX, int LeftY)
{
    // 初めて叩かれたとき
    if (punch_)
    {
        // 右頭、初期座標を登録する
        if (RightX != 0 || RightY != 0)
        {
            for (int i = 0; i < kPartsNum; i++)
            {
                break_parts_[kRHead][i][kPositionX] = (RightX * kSize);
                break_parts_[kRHead][i][kPositionY] = (RightY * kSize);
            }

            // 一度きりなので切り替える
            right_head_ = false;
            punch_ = false;
        }

        // 左頭、初期座標を登録する
        //if (LeftX != 0 || LeftY != 0)
        //{
        //    left_head_ = false;
        //    for (int i = 0; i < kPartsNum; i++)
        //    {
        //        break_parts_[kLHead][i][kPositionX] = (LeftX * kSize);
        //        break_parts_[kLHead][i][kPositionY] = (LeftY * kSize);
        //    }

        //    // 一度きりなので切り替える
        //    punch_ = false;
        //}

        // ジャンプ力の設定
        acceleration_up_ = -kJumpUp;
        acceleration_down_ = -kJumpDown;
    }

    // ここからブロックを落下させる処理を組む
    if (!right_head_)
    {
        for (int i = 0; i < kPartsNum; i++)
        {
            // X座標の移動
            if ((i % 2) == 0)
                break_parts_[kRHead][i][kPositionX] += kSpeed;
            else
                break_parts_[kRHead][i][kPositionX] -= kSpeed;

            // Y座標の移動
            if (i < 2)
            {
                break_parts_[kRHead][i][kPositionY] += acceleration_up_;
            }
            else
            {
                break_parts_[kRHead][i][kPositionY] += acceleration_down_;
            }
        }
        acceleration_up_ += kGravity;
        acceleration_down_ += kGravity;
    }
}

void BreakBlock::draw(int ScreenOver)
{
    if (!right_head_)
    {
        for (int i = 0; i < kPartsNum; i++)
        {
            int texture_position_x = break_parts_[kRHead][i][kPositionX] - ScreenOver;
            int texture_position_y = break_parts_[kRHead][i][kPositionY];

            DrawRectGraph(
                texture_position_x, (texture_position_y - (kSize * 2)),
                (kSize * 3), kSize, (kSize / 2), (kSize / 2), texture_, TRUE, FALSE);
        }
    }
}

void BreakBlock::finalize()
{
    DeleteGraph(texture_);
}