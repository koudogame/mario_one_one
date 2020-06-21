#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"
#include "release.hpp"

/* NewするClass */
#include "mystery.hpp"
#include "brick.hpp"

constexpr int kBrick = 19;
constexpr int kMystery = 48;

enum RL
{
    kRight, kLeft, kRL
};

enum BodyParts
{
    kShoulder, kHands, kHead, kFoot, kBodyParts
};

enum Position
{
    kX, kY, kPosition
};

class Field
{
public :
    bool initialize(std::fstream& stage);
    void update( int Brx, int Bry, int Blx, int Bly , int Status);
    void draw(int ScreenOver);
    void finalize();

    // 体のポジションをセットする関数
    void setPosition(RL rl, BodyParts parts, Position position, int Movement);

    // 体のマップIdを返す三次元配列
    int getPoint(RL rl, BodyParts parts);

private :
    int  bodyId_[kRL][kBodyParts][kPosition];

    int texture_;              // テクスチャハンドル保存用
    int height_;               // 高さ
    int width_;                // 横幅

    // 数字を設定しなくても増える配列
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};