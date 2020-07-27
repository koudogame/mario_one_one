#pragma once

class PosCollision
{
public :
    // �A�C�e���ƃ}���I�̓����蔻��
    bool getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y );

    // FireBall,�G�̓����蔻��
    bool getFireEnemyCollision( int, int, int, int );

    // �G�ƃ}���I�̓����蔻��
    int getEnemyCollision( int Mario_x, int Mario_y, int Other_x, int Other_y, int Status );


private :
    // ���肷�邽�߂̏����i�[����z��
    int body_[ kRL ][ kBodyParts ][ kPosition ];
};