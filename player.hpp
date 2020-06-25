#include <DxLib.h>
#include "collision.hpp"
#include "release.hpp"


// マリオの状態保存
enum Status
{
    kMario = 0,
    kSuperMario,
    kFireMario
};

class Player :
    public Collision
{
public:
    static constexpr int kSize = 64;
    static constexpr int kSpeed = 6;
    static constexpr int kJumpPower = 25;
    static constexpr int kStartX = 256;
    static constexpr int kStartY = 576;
    static constexpr int kEndLine = 576;
    static constexpr int kDeadLine = 800;
    static constexpr int kSkyBlue = 191;
    static constexpr int kGravity = 1;

    Player( Field* field ) : Collision( field ) {};
    ~Player();
    bool initialize();
    bool update();
    void draw();
    void finalize();

    void animation();                                           // マリオのアニメーション
    void collision();                                           // 足元の衝突判定を行う
    void landing();                                             // 着地したときの処理を行う
    void hit();                                                 // 頭をぶつけたときの判定
    void posCollision();                                        // アイテムに当たったとき

    /*背景の描画を流す数値*/
    inline int getScrollCnt() { return scroll_cnt_; }

    /*マリオの状態をfieldにも知らせる*/
    inline int getStatus() { return status_; }

    /*マリオのポジションを渡す*/
    inline int getPositionX() { return total_movement_x_; }
    inline int getPositionY() { return total_movement_y_; }

    /*頭の当たったとき*/
    inline int getBreakLeftX() { return break_left_x_; }        /*左頭の配列x*/
    inline int getBreakLeftY() { return break_left_y_; }        /*左頭の配列y*/
    inline int getBreakRightX() { return break_right_x_; }      /*右頭の配列x*/
    inline int getBreakRightY() { return break_right_y_; }      /*右頭の配列y*/

private:
    int texture_;              // テクスチャハンドル

    int total_movement_x_;     // 総合移動量x
    int total_movement_y_;     // 総合移動量y

    int pos_x_;                // 座標x
    int pos_y_;                // 座標y 

    int left_;                 // SrcX
    int top_;                  // SrcY

    int right_;                // Width
    int bottom_;               // Height

    int status_;               // マリオの状態
    int past_status_;          // マリオの過去の状態

    int scroll_cnt_;           // 半分をマリオが超えたときにスクロール

    bool gameover_flag_;       // true : 生きている, false : 死んでいる

    int animation_;            // 動いているときの切り取り範囲
    bool direction_;           // true : 右向き, false : 左向き

    int animation_cnt_;        // 動かすためのアニメーション速さ調整 
    bool animation_flag_;      // true : 動く, false : 動かない

    // 過去の状態を保存する
    bool old_right_button_;    // true : 押してない, false : 押しています
    bool old_left_button_;     // true : 押してない, false : 押しています

    // いまの状態を保存する
    bool right_button_;        // true : 押してない, false : 押しています 
    bool left_button_;         // true : 押してない, false : 押しています

    int break_right_x_;        // 右頭のぶつかった座標x
    int break_right_y_;        // 右頭のぶつかった座標y

    int break_left_x_;         // 左頭のぶつかった座標x
    int break_left_y_;         // 左頭のぶつかった座標y
};