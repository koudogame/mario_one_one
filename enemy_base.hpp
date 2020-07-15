#pragma once
#include <Windows.h>
#include <DxLib.h>
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
    int walk_animation_ = -1;       // -1 : 左足, 　　1 : 右足
    int direction_      = -1;       // -1 : 左へ進む, 1 : 右へ進む
    bool burn_ = true;              // true : 焼かれてない, false : 焼死

public :
    static const int kGravity  = 1;
    static const int kSpeed    = 2;
    static const int kJumpPower = 12;
    static const int kMaxSpeed = 12;
    static const int kTurtle   = 36;
    static const int kNoBlock  = 119;
    static const int kShell    = 113;
    static const int kGround   = 575;


    EnemyBase( Field* field ) : Collision( field ) {};
    virtual void initialize( const int Id, const RECT Rect, const int X, const int Y );
    virtual void update(int ScreenOver);
    virtual void draw( int Texture, int ScreenOver );
    
    void fireCollision();
    void changeDirection();

    virtual bool getPushFlag();
    virtual int getPosX();
    virtual int getPosY();
    virtual void posCollision(int Touch);
    virtual void shellCollision();

    inline const int getId() { return enemy_parts_.Id; }
    inline const int getPositionX() { return enemy_parts_.x; }
    inline const int getPositionY() { return enemy_parts_.y; }
    inline void setPosition( const int& X, const int& Y ) { enemy_parts_.x = X, enemy_parts_.y = Y; }
};