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

public :
    static const int kGravity = 1;

    EnemyBase( Field* field ) : Collision( field ) {};
    virtual void initialize( const int Id, const RECT Rect, const int X, const int Y );
    virtual void update(int ScreenOver);
    virtual void draw( int Texture, int ScreenOver );

    virtual int getPosX();
    virtual int getPosY();
    virtual void posCollision();

    inline const int getId() { return enemy_parts_.Id; }
    inline const int getPositionX() { return enemy_parts_.x; }
    inline const int getPositionY() { return enemy_parts_.y; }
    inline void setPosition( const int& X, const int& Y ) { enemy_parts_.x = X, enemy_parts_.y = Y; }
};