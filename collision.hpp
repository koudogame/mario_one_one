#pragma once
#include "field.hpp"

class Collision
{
public:
    const int kStairs     = 32;                       // 階段のブロックID
    const int kTouchLimit = 64;                       // 衝突判定を持つブロック
    const int kNoBlocka   = 190;                      // 何もないブロックID a
    const int kNoBlockb   = 191;                      // 何もないブロックID b

    Collision( Field* Field );                        // 衝突判定のIDを得るためFieldを持つ

    bool sideColl( RL rl );                           // true  (Id >= 65), flase  (Id <= 64);
    int footColl();                                   // return 1(Id <= 64),return 2(Id == 191), return 0 その他
    int fireColl();                                   // return 1(Id <= 64),return 2(Id == 191),return 3(Id == 32), return 0 その他
    int collision( RL, BodyParts );                   // 当たっているブロックIdを返却する関数

protected:
    int acceleration_;                                // ジャンプ力を付与
    int jumping_;                                     // 0 : 飛べる, 1 : 飛べない, 2 : 何もしない
    int body_[ kRL ][ kBodyParts ][ kPosition ];      // 数値格納用

private:
    Field* field_;
};