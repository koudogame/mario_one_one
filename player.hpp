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
    static const int kMaxHigh = 352;
    static const int kSize = 64;
    static const int kSpeed = 6;
    static const int kDashSpeed = 10;
    static const int kStopper = 16;
    static const int kEnemyJump = 15;
    static const int kJumpPower = 24;
    static const int kDownCnt = 66;
    static const int kTurnCnt = 90;
    static const int kStartX = 256;
    static const int kStartY = 576;
    static const int kEndLine = 576;
    static const int kDeadLine = 800;
    static const int kSkyBlue = 191;
    static const int kGravity = 1;
    static const int kInvincible = 120;
    static const int kDownSpeed = 6;

    Player( Field* field ) : Collision( field ) {};
    ~Player();
    bool initialize();
    bool update();
    void draw();
    void finalize();

    void animation();                                            // マリオのアニメーション
    void collision();                                            // 足元の衝突判定を行う
    void landing();                                              // 着地したときの処理を行う
    void hit();                                                  // 頭をぶつけたときの判定
    void itemCollision();                                        // アイテムに当たったとき
    void enemyCollision();                                       // ぶつかったときの処理
    void enemyStepon();                                          // 踏みつけたときの処理      
    void Ending();                                               // エンディング処理

    /*背景の描画を流す数値*/
    inline int getScrollCnt() { return scroll_cnt_; }

    /*マリオの状態をfieldにも知らせる*/
    inline int getStatus() { return status_; }

    /*無敵状態か確認*/
    inline bool getInvincible() { return invincible_; }

    /*ゴールしているか*/
    inline bool getGoal() { return goal_flag_; }

    inline int getDirection() 
    {
        if( direction_ ) return 1;
        else return -1;
    }

    /*マリオの画面座標を渡す*/
    inline int getPosX() { return pos_x_; }
    inline int getPosY() { return pos_y_; }

    /*マリオのポジションを渡す*/
    inline int getPositionX() { return total_movement_x_; }
    inline int getPositionY() { return total_movement_y_; }

    /*頭の当たったとき*/
    inline int getBreakLeftX() { return break_left_x_; }        /*左頭の配列x*/
    inline int getBreakLeftY() { return break_left_y_; }        /*左頭の配列y*/
    inline int getBreakRightX() { return break_right_x_; }      /*右頭の配列x*/
    inline int getBreakRightY() { return break_right_y_; }      /*右頭の配列y*/
    
    inline bool getEnd() { return extinguish_existence_; }      /*存在が消えたら*/

    inline bool getGameover() { return gameover_flag_; }        /*死んでいるか*/

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

    int invincible_cnt_;       // 無敵時間の計測
    bool invincible_;          // true : ぶつかる, false : 無敵状態

    bool catch_flag_;          // true : 掴まっていない, false : 掴んでいる
    bool goal_flag_;           // true : ゴールしていない, false : ゴールしている
    bool extinguish_existence_;// flase : 存在を消す

    int down_cnt_;             // この値が66になったら向き反転
    int throw_cnt_;            // 投げるモーションの維持
    bool throw_flag_;            // 投げるモーションの維持

    int push_time_jump_;       // 1 = Pressed,2 <= Held
    int push_time_fire_;       // 1 = Pressed,2 <= Held
    int push_time_run_;        // 1 = Pressed,2 <= Held
    int push_time_squat_;      // 1 = Pressed,2 <= Held
};