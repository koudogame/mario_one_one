#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"
#include "release.hpp"

/* NewするClass */
#include "mystery.hpp"
#include "brick.hpp"

const int kBrick   = 19;
const int kMystery = 48;
const int kSize    = 64;
const int kNoblock = 190;

namespace breakblock
{
    enum BreakParts
    {
        kRightUp, kRightDown, kLeftUp, kLeftDown, kBreakParts
    };

    enum Vector2
    {
        kPositionX, kPositionY, kVector2
    };
}

using namespace breakblock;

class Field
{
public :
    bool initialize(std::fstream& stage);
    void update( int Brx, int Bry, int Blx, int Bly , int Status);
    void draw(int ScreenOver);
    void drawFront( int ScreenOver );
    void finalize();

    // 叩かれたブロックを上げ下げする関数
    void downBlock();

    // 体のマップIdを返す三次元配列
    int getId( int PosX, int PosY );

private :
    int texture_;              // テクスチャハンドル保存用
    int height_;               // 高さ
    int width_;                // 横幅
    int block_rx_;              // 多重updateを防ぐため
    int block_ry_;              // 多重updateを防ぐため
    int block_lx_;              // 多重updateを防ぐため
    int block_ly_;              // 多重updateを防ぐため

                               // 数字を設定しなくても増える配列
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};