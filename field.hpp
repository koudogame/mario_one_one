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

class Field
{
public :
    bool initialize(std::fstream& stage);
    void update( int Brx, int Bry, int Blx, int Bly , int Status);
    void draw(int ScreenOver);
    void finalize();

    void downBlock();

    // 体のマップIdを返す三次元配列
    int getId( int PosX, int PosY );

private :
    int texture_;              // テクスチャハンドル保存用
    int height_;               // 高さ
    int width_;                // 横幅

    // 数字を設定しなくても増える配列
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};