#pragma once
#include <Windows.h>
#include <DxLib.h>
#include "collision.hpp"


// パーツ構造体
struct ItemParts
{
    int Id;
    RECT rect;
    int x, y;

    ItemParts()
    {
        Id = 0;
        rect = { 0L };
        x = 0, y = 0;
    }
};

class ItemBase :
    public Collision
{
protected:
    ItemParts item_;
    bool up_;
    int status_;

public:
    static const int kGravity  = 1;

    ItemBase( Field* field ) : Collision( field ) {};
    virtual bool initialize( const int Id, const RECT Rect, const int X, const int Y );
    virtual void update(int Screenover);
    virtual void draw( int Texture, const int Screenover );
    virtual void flagChange( int Status );

    inline const int getId() { return item_.Id; }
    inline const int getPositionX() { return item_.x; }
    inline const int getPositionY() { return item_.y; }
    inline void setPosition( const int& X, const int& Y ) { item_.x = X, item_.y = Y; }
};