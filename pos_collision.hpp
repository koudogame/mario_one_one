#pragma once

namespace posCollision
{
    enum RorL
    {
        kRight, kLeft, kSide
    };

    enum Body
    {
        kShoulder, kHands, kHead, kFoot, kBody
    };

    enum Pos
    {
        kX, kY, kPos
    };
}

using namespace posCollision;

class PosCollision
{
public :
    const int kSize = 64;

    // アイテムとマリオの当たり判定
    bool getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y );

    // FireBall,敵の当たり判定
    bool getFireEnemyCollision( int, int, int, int );

    // 敵とマリオの当たり判定
    int getEnemyCollision( int Mario_x, int Mario_y, int Other_x, int Other_y, int Status );

private :
    int body_[ kSide ][ kBody ][ kPos ];
};