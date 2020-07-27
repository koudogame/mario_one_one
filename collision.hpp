#pragma once
#include "field.hpp"

class Collision
{
public:
    const int kStairs     = 32;                       // �K�i�̃u���b�NID
    const int kTouchLimit = 64;                       // �Փ˔�������u���b�N
    const int kNoBlocka   = 190;                      // �����Ȃ��u���b�NID a
    const int kNoBlockb   = 191;                      // �����Ȃ��u���b�NID b

    Collision( Field* Field );                        // �Փ˔����ID�𓾂邽��Field������

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