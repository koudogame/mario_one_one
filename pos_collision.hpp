#pragma once

class PosCollision
{
public :
    // アイテムとマリオの当たり判定
    bool getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y );

    // FireBall,敵の当たり判定
    bool getFireEnemyCollision( int, int, int, int );

    // 敵とマリオの当たり判定
    int getEnemyCollision( int Mario_x, int Mario_y, int Other_x, int Other_y, int Status );


private :
    // 判定するための情報を格納する配列
    int body_[ kRL ][ kBodyParts ][ kPosition ];
};