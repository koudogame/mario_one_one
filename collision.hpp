#pragma once
#include "field.hpp"

namespace collision
{
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
    int footColl();                                   // return 1(Id <= 64),return 2(Id == 191), return 0 その他
    int fireColl();                                   // return 1(Id <= 64),return 2(Id == 191),return 3(Id == 32), return 0 その他
    int collision( RL, BodyParts );

protected:
    int acceleration_;                                // ジャンプ力を付与
    int jumping_;                                     // 0 : 飛べる, 1 : 飛べない, 2 : 何もしない
    int body_[ kRL ][ kBodyParts ][ kPosition ];      // 数値格納用

private:
    Field* field_;
};