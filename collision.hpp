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

enum JumpFlag
{
    kJump, kNoJump, kNoMove
};

class Collision
{
public:
    const int kSize = 64;
    Collision( Field* Field );

    bool sideColl( RL rl );                           // true  (Id >= 65), flase  (Id <= 64);
    int footColl();                                   // return 1(Id <= 64),return 2(Id == 191), return 0 その他
    int collision( RL, BodyParts );

    void setMarioPos( int PosX, int PosY );           // マリオのポジションをセット
    void setItemPos( int PosX, int PosY );            // アイテムのポジションをセット

    bool getCollision(int Status);                              // true : 衝突していない, false : 衝突している 

protected:
    int acceleration_;                                // ジャンプ力を付与
    int jumping_;                                     // 0 : 飛べる, 1 : 飛べない, 2 : 何もしない
    int body_[ kRL ][ kBodyParts ][ kPosition ];      // 数値格納用

private:
    Field* field_;

    /* 同じ画面にいるので画面座標で管理する */

    // マリオのポジションを保存  
     int mario_pos_x_;
     int mario_pos_y_;

    // アイテムの場所を保存( 呼ばれるたびに更新 )
     int item_pos_x_;
     int item_pos_y_;
};