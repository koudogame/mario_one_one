#pragma once
#include<DxLib.h>
#include "fire_factory.hpp"
#include "collision.hpp"

class BallManagement
{
public :
    BallManagement( Field* field ) : ff_( field ) { field_ = field; }

    void initialize();
    void update( int, int, int, int, bool ); // position_x_, position_y_, status_, direction_, gameoverflag;
    void draw(const int);              // ScreenOver
    void finalize();

    void posCheck(const int);                   // ファイアボールの場所をチェックする
    void enemyCollision( int );        // 当たったときの火を消す

    int getFirePosX(int);              // fireのX座標を返す
    int getFirePosY(int);              // fireのY座標を返す

    int getSize();                     // for文用にサイズを返す

private: 

    Field* field_;
    FireFactory ff_;

    int texture_;
    int push_create_fire_;             // 単発生成できるよう時間管理

    // 全体ファイア管理用配列
    std::vector<FireFactory*> fire_;
};

// fire_factoryをすべて統括して管理するのですべてを操作する必要がある。