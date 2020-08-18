#pragma once

// 構造体
struct PlayerData
{
    Position<int> break_right;      // 叩いた右頭座標
    Position<int> break_left;       // 叩いた左頭座標

    Position<int> player_position;  // Player画面座標
    Position<int> total_position;   // Player合計座標
    
    int player_status;              // Player状態
    int push_squat;                 // しゃがみ押している時間
    int scroll_cnt;                 // 画面が動いた量
    int direction;                  // 向いている向き

    bool end_flag;                  // true : 塔外        , false : 塔内
    bool goal_flag;                 // true : ゴール前    , false : ゴール後
    bool gameover_flag;             // true : 死亡前      , false : 死亡後
    bool invincible_flag;           // true : 無敵じゃない, false : 無敵
};