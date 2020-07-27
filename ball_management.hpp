#pragma once
#include "fire_factory.hpp"
#include "collision.hpp"

class BallManagement
{
public :
    const int kBallLimit = 4;    // 連続で出せる数を設定
    const int kStopper   = 16;   // 連射防止数値
    const int kEndline   = 640;  // 行ってはいけない座標

    BallManagement( Field* field ) : ff_( field ) { field_ = field; }

    void initialize();
    void update( int, int, int, int, bool ,int);
    void draw(const int);              // ScreenOver
    void finalize();

    void createFire(int, int, int, int);
    void sideCheck();
    void posCheck(const int);          // ファイアボールの場所をチェックする
    void enemyCollision( int );        // 当たったときの火を消す

    int getFirePosX(int);              // fireのX座標を返す
    int getFirePosY(int);              // fireのY座標を返す

    int getSize();                     // for文用にサイズを返す

private: 

    Field* field_;
    FireFactory ff_;

    int texture_;
    int push_create_fire_;             // 単発生成できるよう時間管理

    int create_cnt_;                   // 次回生成までの時間計測
    bool create_flag_;                 // 生成切り替え

    // 全体ファイア管理用配列
    std::vector<FireFactory*> fire_;
};

// fire_factoryをすべて統括して管理するのですべてを操作する必要がある。