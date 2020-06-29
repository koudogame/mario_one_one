#include "pos_collision.hpp"

bool PosCollision::getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y )
{
    // 矩形と矩形の当たり判定
    {
        int mario_left = Mario_x;
        int mario_right = Mario_x + kSize;

        int mario_top = Mario_y;
        int mario_bottom = Mario_y + kSize;

        int other_left = Other_x;
        int other_right = Other_x + kSize;
           
        int other_top = Other_y;
        int other_bottom = Other_y + kSize;

        // 4本の軸の判定
        if( (mario_right > other_left) && (other_right > mario_left)
            && (mario_bottom > other_top) && (other_bottom > mario_top) )
        {
            // 衝突しています
            return false;
        }

        // 衝突していません
        return true;
    }
}

int PosCollision::getEnemyCollision( int Mario_x, int Mario_y, int Enemy_x, int Enemy_y, int Status )
{
    int enemy_x1 = Enemy_x;
    int enemy_x2 = Enemy_x + kSize;

    int enemy_y1 = Enemy_y;
    int enemy_y2 = Enemy_y + kSize;

    // 右足1, 左足2, 右手3, 左手4
    body_[ kRight ][ kFoot ][ kX ] = (Mario_x + (kSize - 10));
    body_[ kLeft ][ kFoot ][ kX ] = (Mario_x + 10);

    // 小さいときか大きいときか
    if( Status == 0 )
    {
        body_[ kRight ][ kFoot ][ kY ] = (Mario_y + kSize + 1);
        body_[ kLeft ][ kFoot ][ kY ] = (Mario_y + kSize + 1);
    }
    else
    {
        body_[ kRight ][ kFoot ][ kY ] = (Mario_y + (kSize * 2) + 1);
        body_[ kLeft ][ kFoot ][ kY ] = (Mario_y + (kSize * 2) + 1);
    }

    if( enemy_x1 <= body_[ kRight ][ kFoot ][ kX ] && body_[ kRight ][ kFoot ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kRight ][ kFoot ][ kY ] && body_[ kRight ][ kFoot ][ kY ] <= enemy_y2 ||
        enemy_x1 <= body_[ kLeft ][ kFoot ][ kX ] && body_[ kLeft ][ kFoot ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kLeft ][ kFoot ][ kY ] && body_[ kLeft ][ kFoot ][ kY ] <= enemy_y2 )
    {
        return 1;       // 足が敵と当たっている
    }

    return 0;
}
