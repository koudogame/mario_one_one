#pragma once
#include "collision.hpp"

// パーツ構造体
struct EnemyParts
{
    int Id;
    RECT rect;
    int x, y;

    EnemyParts()
    {
        Id = 0;
        rect = { 0L };
        x = 0, y = 0;
    }
};

class EnemyBase :
    public Collision
{
protected :
    EnemyParts enemy_parts_;

    int animation_      = 0;
    int walk_animation_ = -1;               // -1 : 左足, 　　1 : 右足
    int direction_      = -1;               // -1 : 左へ進む, 1 : 右へ進む
    bool burn_ = true;                      // true : 焼かれてない, false : 焼死

public :
    const int kSpeed     = 2;               // 速さ
    const int kCountup   = 8;               // アニメーション
    const int kJumpPower = 12;              // ジャンプ力
    const int kMaxSpeed  = 12;              // 最高スピード
    const int kNoBlock   = 119;             // 何もないマップID
    const int kGround    = 575;             // 床最低ライン


    EnemyBase( Field* field ) : Collision( field ) {};
    virtual void initialize( const int Id, const RECT Rect, const int X, const int Y );
    virtual void update(int ScreenOver);
    virtual void draw( int Texture, int ScreenOver );

    virtual bool getPushFlag();            
    virtual int getPosX();
    virtual int getPosY();
    virtual void fireCollision();           // ファイアと衝突したとき
    virtual void posCollision(int Touch);   // マリオと衝突したとき
    virtual void shellCollision();          // 甲羅状態で衝突したとき
    virtual void changeDirection();         // 方向を変える関数

    inline const int getId() { return enemy_parts_.Id; }
    inline const int getPositionX() { return enemy_parts_.x; }
    inline const int getPositionY() { return enemy_parts_.y; }
    inline void setPosition( const int& X, const int& Y ) { enemy_parts_.x = X, enemy_parts_.y = Y; }
};