#pragma once

namespace posCollision
{
    // �̂̍��E
    enum RorL
    {
        kRight, kLeft, kSide
    };

    // �̂̃p�[�c
    enum Body
    {
        kShoulder, kHands, kHead, kFoot, kBody
    };

    // �|�W�V����X, Y
    enum Pos
    {
        kX, kY, kPos
    };
}

using namespace posCollision;

class PosCollision
{
public :
    const int kGather     = 10;       // �񂹂Ă����(position)
    const int kHalfSize   = 32;       // �u���b�N�����̑傫��
    const int kSize       = 64;       // �u���b�N�T�C�Y
    const int kDoubleSize = 128;      // �u���b�N2�{�̑傫��
    const int kQuadruple  = 256;      // �u���b�N4�{�̑傫��


    // �A�C�e���ƃ}���I�̓����蔻��
    bool getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y );

    // FireBall,�G�̓����蔻��
    bool getFireEnemyCollision( int, int, int, int );

    // �G�ƃ}���I�̓����蔻��
    int getEnemyCollision( int Mario_x, int Mario_y, int Other_x, int Other_y, int Status );


private :
    // ���肷�邽�߂̏����i�[����z��
    int body_[ kSide ][ kBody ][ kPos ];    
};