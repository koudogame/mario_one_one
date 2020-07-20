#pragma once
#include "field.hpp"

namespace collision
{
    // �̂̉E�A��
    enum RL
    {
        kRight, kLeft, kRL
    };

    //�@�̂̃p�[�c
    enum BodyParts
    {
        kShoulder, kHands, kHead, kFoot, kBodyParts
    };

    //�@�̂̃p�[�c��X,Y
    enum Position
    {
        kX, kY, kPosition
    };

    // ��я�Ԃ𖾊m�ɂ���
    enum JumpFlag
    {
        kJump, kNoJump, kNoMove
    };
}

using namespace collision;

class Collision
{
public:
    const int kStairs = 32;
    const int kSize = 64;
    Collision( Field* Field );

    bool sideColl( RL rl );                           // true  (Id >= 65), flase  (Id <= 64);
    int footColl();                                   // return 1(Id <= 64),return 2(Id == 191), return 0 ���̑�
    int fireColl();                                   // return 1(Id <= 64),return 2(Id == 191),return 3(Id == 32), return 0 ���̑�
    int collision( RL, BodyParts );                   // �������Ă���u���b�NId��ԋp����֐�

protected:
    int acceleration_;                                // �W�����v�͂�t�^
    int jumping_;                                     // 0 : ��ׂ�, 1 : ��ׂȂ�, 2 : �������Ȃ�
    int body_[ kRL ][ kBodyParts ][ kPosition ];      // ���l�i�[�p

private:
    Field* field_;
};