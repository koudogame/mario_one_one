#pragma once
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
    Item( Field* Field );
    bool initialize( std::fstream& stage );
    void update( PlayerData );
    void draw( int Screenover );
    void finalize();

    void coinCheckRight( int, int );
    void coinCheckLeft( int, int );

    void posCollision( int i, int j );      // マリオと当たったときに呼ばれる関数
    void getGoal( bool );
    void getEnd( bool );

    inline int getItemPosX( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosX(); }
    inline int getItemPosY( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosY(); }
    inline int getWidth() { return width_; }
    inline int getHeight() { return height_; }
    inline int getId( int i, int j ) { return item_[ 0 ][ i ][ j ]->getId(); }
    inline int getCoin() { return coin_counter_; }

private:
    Field* field_;

    int texture_;                 // テクスチャハンドル保存用
    int width_;                   // 横幅
    int height_;                  // 高さ
    
    Position<int> double_touch_;  
    Position<int> past_r_;
    Position<int> past_l_;

    int coin_counter_;            // コインのカウンター

    // マップチップ配列
    std::vector<std::vector<std::vector<ItemBase*>>> item_;
};