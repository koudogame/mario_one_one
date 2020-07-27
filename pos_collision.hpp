#pragma once

namespace posCollision
{
    // 体の左右
    enum RorL
    {
        kRight, kLeft, kSide
    };

    // 体のパーツ
    enum Body
    {
        kShoulder, kHands, kHead, kFoot, kBody
    };

    // ポジションX, Y
    enum Pos
    {
        kX, kY, kPos
    };
}

using namespace posCollision;

class PosCollision
{
public :
    const int kGather     = 10;       // 寄せている量(position)
    const int kHalfSize   = 32;       // ブロック半分の大きさ
    const int kSize       = 64;       // ブロックサイズ
    const int kDoubleSize = 128;      // ブロック2倍の大きさ
    const int kQuadruple  = 256;      // ブロック4倍の大きさ


    // アイテムとマリオの当たり判定
    bool getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y );

    // FireBall,敵の当たり判定
    bool getFireEnemyCollision( int, int, int, int );

    // 敵とマリオの当たり判定
    int getEnemyCollision( int Mario_x, int Mario_y, int Other_x, int Other_y, int Status );


private :
    // 判定するための情報を格納する配列
    int body_[ kSide ][ kBody ][ kPos ];    
};