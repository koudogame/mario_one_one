#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"
#include "both_hands.hpp"
#include "release.hpp"


class Field
{
public :
    bool initialize(std::fstream& stage);
    void update();
    void draw(int ScreenOver);
    void finalize();

    // 体の右側
    int getRightShoulderId( Side side_ );
    int getRightHandId( Side side_ );
    // 体の左側
    int getLeftShoulderId( Side side_ );
    int getLeftHandId( Side side_ );

private :
    Side side_;

    int texture_;              // テクスチャハンドル保存用
    int height_;               // 高さ
    int width_;                // 横幅

    // 数字を設定しなくても増える配列
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};