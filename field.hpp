#pragma once
#include "block_base.hpp"
#include "release.hpp"
#include "namespace.hpp"

/* NewするClass */
#include "mystery.hpp"
#include "brick.hpp"

const int kNoblock = 190; // 何もないブロックID


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
    void update( PlayerData );
    void draw(int ScreenOver);
    void drawFront( int ScreenOver );
    void finalize();

    // 叩かれたブロックを上げ下げする関数
    void downBlock();

    // 体のマップIdを返す三次元配列
    int getId( int PosX, int PosY );

private :
    Position<int> block_right_;
    Position<int> block_left_;

    int texture_;              // テクスチャハンドル保存用
    int height_;               // 高さ
    int width_;                // 横幅

    // 数字を設定しなくても増える配列
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};