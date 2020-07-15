#pragma once
#include <Windows.h>
#include <DxLib.h>
#include "collision.hpp"

// �p�[�c�\����
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
    int walk_animation_ = -1;       // -1 : ����, �@�@1 : �E��
    int direction_      = -1;       // -1 : ���֐i��, 1 : �E�֐i��
    bool burn_ = true;              // true : �Ă���ĂȂ�, false : �Ď�

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