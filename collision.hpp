#pragma once
#include "field.hpp"

enum RL
{
    kRight, kLeft, kRL
};

enum BodyParts
{
    kShoulder, kHands, kHead, kFoot, kBodyParts
};

enum Position
{
    kX, kY, kPosition
};

class Collision
{
public :
    Collision( Field* Field );
    virtual int collision( RL, BodyParts );

protected :
    int body_[ kRL ][ kBodyParts ][ kPosition ];                /*êîíläiî[óp*/

private :
    Field* field_;
};