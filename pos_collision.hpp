#pragma once

class PosCollision
{
public :
    const int kSize = 64;

    // アイテムとマリオの当たり判定
    bool getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y );

private :
};