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

    // �A�C�e���ƃ}���I�̓����蔻��
    bool getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y );

    // FireBall,�G�̓����蔻��
    bool getFireEnemyCollision( int, int, int, int );

    // �G�ƃ}���I�̓����蔻��
    int getEnemyCollision( int Mario_x, int Mario_y, int Other_x, int Other_y, int Status );

private :
    int body_[ kSide ][ kBody ][ kPos ];
};