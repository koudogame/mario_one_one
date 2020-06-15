#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"

class Field
{
public :
    bool initialize(std::fstream& stage);
    void update(int Texture, int ScreenOver);
    void finalize();

private :
    int texture_;              // テクスチャハンドル保存用
    int height_;               // 高さ
    int width_;                // 横幅

    // 数字を設定しなくても増える配列
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};