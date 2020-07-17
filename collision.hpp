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
    int footColl();                                   // return 1(Id <= 64),return 2(Id == 191), return 0 ‚»‚Ì‘¼
    int fireColl();                                   // return 1(Id <= 64),return 2(Id == 191),return 3(Id == 32), return 0 ‚»‚Ì‘¼
    int collision( RL, BodyParts );

protected:
    int acceleration_;                                // ƒWƒƒƒ“ƒv—Í‚ð•t—^
    int jumping_;                                     // 0 : ”ò‚×‚é, 1 : ”ò‚×‚È‚¢, 2 : ‰½‚à‚µ‚È‚¢
    int body_[ kRL ][ kBodyParts ][ kPosition ];      // ”’lŠi”[—p

private:
    Field* field_;
};