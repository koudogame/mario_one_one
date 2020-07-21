#pragma once
#include <vector>
#include <fstream>
#include "item_base.hpp"
#include "release.hpp"
#include "field.hpp"

/* NewするClass */
#include "coin.hpp"
#include "power_up.hpp"
#include "goal.hpp"
#include "castle_flag.hpp"


class Item
{
public:
    const int kFlag     = 3;        // 旗ID
    const int kPowerup  = 0;        // キノコID
    const int kPowerup2 = 16;       // フラワーID
    const int kGoal     = 19;       // ゴールID
    const int kCoin     = 80;       // コインID
    const int kItemsize = 64;       // アイテムの大きさ

    Item( Field* Field );
    bool initialize( std::fstream& stage );
    void update( int Brx, int Bry, int Blx, int Bly, int Status, int Screenover );
    void draw( int Screenover );
    void finalize();

    void posCollision( int i, int j );      // マリオと当たったときに呼ばれる関数
    void getGoal( bool );
    void getEnd( bool );

    inline int getItemPosX( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosX(); }
    inline int getItemPosY( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosY(); }
    inline int getWidth() { return width_; }
    inline int getHeight() { return height_; }
    inline int getId( int i, int j ) { return item_[ 0 ][ i ][ j ]->getId(); }

private:
    Field* field_;

    int texture_;       // テクスチャハンドル保存用
    int width_;         // 横幅
    int height_;        // 高さ

    // マップチップ配列
    std::vector<std::vector<std::vector<ItemBase*>>> item_;
};