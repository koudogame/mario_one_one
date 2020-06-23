#pragma once
#include <vector>
#include <fstream>
#include "item_base.hpp"
#include "release.hpp"
#include "field.hpp"

/* NewするClass */
#include "coin.hpp"

constexpr int kCoin = 48;
constexpr int kItemsize = 64;

/* NewするClass */

class Item
{
public :
    Item( Field* Field );
    bool initialize( std::fstream& stage );
    void update( int Brx, int Bry, int Blx, int Bly, int Status );
    void draw( int Screenover );
    void finalize();

private :  
    Field* field_;

    int texture_;       // テクスチャハンドル保存用
    int height_;        // 高さ
    int width_;         // 横幅

    // マップチップ配列
    std::vector<std::vector<std::vector<ItemBase*>>> item_;
};