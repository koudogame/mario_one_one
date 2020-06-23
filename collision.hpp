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
   
    bool sideColl(RL rl);                           // true  (Id >= 65), flase  (Id <= 64);
    int footColl();                                 // return 1(Id <= 64),return 2(Id == 191), return 0 ���̑�
    int collision( RL, BodyParts );

protected :
    int acceleration_;                              // �W�����v�͂�t�^
    bool jumping_;                                  // true : ��ׂ�, false : ��ׂȂ�

    int body_[ kRL ][ kBodyParts ][ kPosition ];    // ���l�i�[�p

private :
    Field* field_;
};