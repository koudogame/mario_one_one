#pragma once
#include <vector>
#include <fstream>
#include "item_base.hpp"
#include "release.hpp"
#include "field.hpp"

/* NewするClass */
#include "coin.hpp"
#include "power_up.hpp"

constexpr int kPowerup  = 0;
constexpr int kPowerup2 = 16;
constexpr int kCoin     = 48;
constexpr int kItemsize = 64;

/* NewするClass */

class Item
{
public :
    Item( Field* Field );
    bool initialize( std::fstream& stage );
    void update( int Brx, int Bry, int Blx, int Bly, int Status, int Screenover );
    void draw( int Screenover );
    void finalize();

    int getItemPosX( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosX(); }
    int getItemPosY( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosY(); }

    int getWidth() { return width_; }
    int getHeight() { return height_; }

    int getID( int i, int j ) { return item_[ 0 ][ i ][ j ]->getId(); }
    void posCollision( int i, int j );

private :  
    Field* field_;

    int texture_;       // テクスチャハンドル保存用
    int height_;        // 高さ
    int width_;         // 横幅
    
    // マップチップ配列
    std::vector<std::vector<std::vector<ItemBase*>>> item_;
};