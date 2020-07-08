#pragma once
#include<DxLib.h>
#include "fire_factory.hpp"
#include "collision.hpp"

class BallManagement
{
public :
    BallManagement( Field* field ) : ff_( field ) { field_ = field; }

    void initialize();
    void update( int, int, int, int ); // position_x_, position_y_, status_, direction_;
    void draw(const int);              // ScreenOver
    void finalize();

    int getFirePosX(int);              // fireのX座標を返す
    int getFirePosY(int);              // fireのY座標を返す

    int getSize();                     // for文用にサイズを返す

private: 
    Field* field_;
    FireFactory ff_;

    int texture_;

    // 全体ファイア管理用配列
    std::vector<FireFactory*> fire_;
};

// fire_factoryをすべて統括して管理するのですべてを操作する必要がある。