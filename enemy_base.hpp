#pragma once
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
    int walk_animation_ = -1;               // -1 : ����, �@�@1 : �E��
    int direction_      = -1;               // -1 : ���֐i��, 1 : �E�֐i��
    bool burn_ = true;                      // true : �Ă���ĂȂ�, false : �Ď�

public :
    const int kSpeed     = 2;               // ����
    const int kCountup   = 8;               // �A�j���[�V����
    const int kJumpPower = 12;              // �W�����v��
    const int kMaxSpeed  = 12;              // �ō��X�s�[�h
    const int kNoBlock   = 119;             // �����Ȃ��}�b�vID
    const int kGround    = 575;             // ���Œ჉�C��


    EnemyBase( Field* field ) : Collision( field ) {};
    virtual void initialize( const int Id, const RECT Rect, const int X, const int Y );
    virtual void update(int ScreenOver);
    virtual void draw( int Texture, int ScreenOver );

    virtual bool getPushFlag();            
    virtual int getPosX();
    virtual int getPosY();
    virtual void fireCollision();           // �t�@�C�A�ƏՓ˂����Ƃ�
    virtual void posCollision(int Touch);   // �}���I�ƏՓ˂����Ƃ�
    virtual void shellCollision();          // �b����ԂŏՓ˂����Ƃ�
    virtual void changeDirection();         // ������ς���֐�

    inline const int getId() { return enemy_parts_.Id; }
    inline const int getPositionX() { return enemy_parts_.x; }
    inline const int getPositionY() { return enemy_parts_.y; }
    inline void setPosition( const int& X, const int& Y ) { enemy_parts_.x = X, enemy_parts_.y = Y; }
};