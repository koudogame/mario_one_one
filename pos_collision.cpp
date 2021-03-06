#include "pos_collision.hpp"
    
// 矩形と矩形の当たり判定
bool PosCollision::getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y )
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

// ファイアと敵の衝突判定
bool PosCollision::getFireEnemyCollision( int Fire_x, int Fire_y, int Enemy_x, int Enemy_y)
{
    int fire_left    = Fire_x;
    int fire_right   = Fire_x + kHalfSize;

    int fire_top     = Fire_y + kQuadruple;
    int fire_bottom  = Fire_y + kHalfSize + kQuadruple;

    int enemy_left   = Enemy_x;
    int enemy_right  = Enemy_x + kSize;

    int enemy_top    = Enemy_y;
    int enemy_bottom = Enemy_y + kSize;

    // 4本の軸の判定
    if( (fire_right > enemy_left) && (enemy_right > fire_left)
    && (fire_bottom > enemy_top) && (enemy_bottom > fire_top) )
    {
        // 衝突しています
        return false;
    }

    // 衝突していません
    return true;
}


// マリオと敵の衝突判定
int PosCollision::getEnemyCollision( int Mario_x, int Mario_y, int Enemy_x, int Enemy_y, int Status )
{
    int enemy_x1 = Enemy_x;
    int enemy_x2 = Enemy_x + kSize;

    int enemy_y1 = Enemy_y;
    int enemy_y2 = Enemy_y + kSize;


    // 足元の登録
    body_[ kRight ][ kFoot ][ kX ] = (Mario_x + (kSize - kGather));
    body_[ kLeft ][ kFoot ][ kX ] = (Mario_x + kGather);

    // 小さいときか大きいときか
    if( Status == kMario )
    {
        body_[ kRight ][ kFoot ][ kY ] = (Mario_y + kSize + 1);             // ひとつ先の大きさ
        body_[ kLeft ][ kFoot ][ kY ] = (Mario_y + kSize + 1);              // ひとつ先の大きさ
    }
    else
    {
        body_[ kRight ][ kFoot ][ kY ] = (Mario_y + kDoubleSize + 1);       // ひとつ先の大きさ
        body_[ kLeft ][ kFoot ][ kY ] = (Mario_y + kDoubleSize + 1);        // ひとつ先の大きさ
    }


    // 右体の登録
    body_[ kRight ][ kShoulder ][ kX ] = (Mario_x + kSize + 1);             // ひとつ先の大きさ
    body_[ kRight ][ kShoulder ][ kY ] = (Mario_y + kGather);
    body_[ kRight ][ kHands ][ kX ] = (Mario_x + kSize + 1);                // ひとつ先の大きさ

    // 小さいときか大きいときか
    if( Status == kMario )
        body_[ kRight ][ kHands ][ kY ] = (Mario_y + kSize - kGather);
    else
        body_[ kRight ][ kHands ][ kY ] = (Mario_y + kDoubleSize - kGather);



    // 左体の登録
    body_[ kLeft ][ kShoulder ][ kX ] = (Mario_x - 1);                      // ひとつ先の大きさ
    body_[ kLeft ][ kShoulder ][ kY ] = (Mario_y + kGather);
    body_[ kLeft ][ kHands ][ kX ]    = (Mario_x - 1);                      // ひとつ先の大きさ

    // 小さいときか大きいときか
    if( Status == kMario )
        body_[ kLeft ][ kHands ][ kY ] = (Mario_y + kSize - kGather);
    else
        body_[ kLeft ][ kHands ][ kY ] = (Mario_y + kDoubleSize - kGather);



    // 足が敵と当たっている
    if( enemy_x1 <= body_[ kRight ][ kFoot ][ kX ] && body_[ kRight ][ kFoot ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kRight ][ kFoot ][ kY ] && body_[ kRight ][ kFoot ][ kY ] <= enemy_y2 ||
        enemy_x1 <= body_[ kLeft ][ kFoot ][ kX ] && body_[ kLeft ][ kFoot ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kLeft ][ kFoot ][ kY ] && body_[ kLeft ][ kFoot ][ kY ] <= enemy_y2 )
        return 1;   


    // 右体が敵と当たっている
    else if(
        enemy_x1 <= body_[ kRight ][ kShoulder ][ kX ] && body_[ kRight ][ kShoulder ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kRight ][ kShoulder ][ kY ] && body_[ kRight ][ kShoulder ][ kY ] <= enemy_y2 ||
        enemy_x1 <= body_[ kRight ][ kHands ][ kX ] && body_[ kRight ][ kHands ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kRight ][ kHands ][ kY ] && body_[ kRight ][ kHands ][ kY ] <= enemy_y2 )
        return 2;       
    

    // 左体が敵と当たっている
    else if(
        enemy_x1 <= body_[ kLeft ][ kShoulder ][ kX ] && body_[ kLeft ][ kShoulder ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kLeft ][ kShoulder ][ kY ] && body_[ kLeft ][ kShoulder ][ kY ] <= enemy_y2 ||
        enemy_x1 <= body_[ kLeft ][ kHands ][ kX ] && body_[ kLeft ][ kHands ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kLeft ][ kHands ][ kY ] && body_[ kLeft ][ kHands ][ kY ] <= enemy_y2 )
        return 3;       


    return 0;
}
