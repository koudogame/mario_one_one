#include "collision.hpp"

class Player :
    public Collision
{
public:
    const int kSpeed      = 6;      // 歩いているときの速度
    const int kDownSpeed  = 6;      // ゴールしたとき落ちるスピード
    const int kAnimeMove  = 8;      // アニメーション用
    const int kDashSpeed  = 10;     // ダッシュしているときの速度
    const int kEnemyJump  = 15;     // 敵を踏んだ時のジャンプ力
    const int kStopper    = 16;     // 連射防止ストッパー
    const int kJumpPower  = 24;     // ジャンプボタン時のジャンプ力
    const int kDownCnt    = 66;     // 掴んでからの待ち時間
    const int kTurnCnt    = 90;     // 向き反転させるための時間
    const int kInvincible = 180;    // 無敵制限時間
    const int kSkyBlue    = 191;    // 背景の何もない透明マップチップID
    const int kGoalPost   = 194;    // ゴールポスト
    const int kEntrance   = 201;    // 塔の入り口
    const int kStartX     = 256;    // 初期座標X
    const int kStartY     = 576;    // 初期座標Y
    const int kEndLine    = 576;    // 画面の中心
    const int kDeadLine   = 800;    // この数値より下は死ぬ

    Player( Field* field ) : Collision( field ) {};
    bool initialize();
    bool update(bool);
    void draw();
    void finalize();

    void animation();               // マリオのアニメーション
    void collision();               // 足元の衝突判定を行う
    void landing();                 // 着地したときの処理を行う
    void hit();                     // 頭をぶつけたときの判定
    void itemCollision();           // アイテムに当たったとき
    void enemyCollision();          // ぶつかったときの処理
    void enemyStepon();             // 踏みつけたときの処理      
    void ending();                  // エンディング処理
    void rightCheck();              // 体の右側を登録してチェックする関数
    void leftCheck();               // 体の左側を登録してチェックする関数

    inline int getScrollCnt() { return scroll_cnt_; }   /*背景の描画を流す数値*/
    inline int getStatus() { return status_; }          /*マリオの状態をfieldにも知らせる*/
    inline bool getInvincible() { return invincible_; } /*無敵状態か確認*/
    inline bool getInvincibleTime() { return invincible_time_; }
    inline bool getGoal() { return goal_flag_; }        /*ゴールしているか*/

    // 向きに応じて渡す
    inline int getDirection() 
    {
        if( direction_ ) return 1;
        else return -1;
    }

    /*マリオの画面座標を渡す*/
    inline int getPosX() { return position_.x; }
    inline int getPosY() { return position_.y; }

    /*マリオのポジションを渡す*/
    inline int getPositionX() { return total_move_.x; }
    inline int getPositionY() { return total_move_.y; }

    /*頭の当たったとき*/
    inline int getBreakRightX() { return break_right_.x; }      /*右頭の配列x*/
    inline int getBreakRightY() { return break_right_.y; }      /*右頭の配列y*/

    inline int getBreakLeftX() { return break_left_.x; }        /*左頭の配列x*/
    inline int getBreakLeftY() { return break_left_.y; }        /*左頭の配列y*/
    
    inline bool getEnd() { return extinguish_existence_; }      /*存在が消えたら*/
    inline bool getGameover() { return gameover_flag_; }        /*死んでいるか*/

private:
    Rect<int> rect_;           // Rect呼び出し
    Position<int> position_;   // Position呼び出し
    Position<int> total_move_; // Position呼び出し
    Position<int> break_right_;// 頭の右の座標
    Position<int> break_left_; // 頭の左の座標

    int texture_;              // テクスチャハンドル

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

    int invincible_cnt_;       // 無敵時間の計測
    bool invincible_;          // true : ぶつかる, false : 無敵状態
    bool invincible_time_;     // 無敵だが動ける時間

    bool catch_flag_;          // true : 掴まっていない, false : 掴んでいる
    bool goal_flag_;           // true : ゴールしていない, false : ゴールしている
    bool extinguish_existence_;// flase : 存在を消す

    int down_cnt_;             // この値が66になったら向き反転
    int throw_cnt_;            // 投げるモーションの維持
    bool throw_flag_;          // 投げるモーションの維持

    int push_time_jump_;       // 1 = Pressed,2 <= Held
    int push_time_fire_;       // 1 = Pressed,2 <= Held
    int push_time_run_;        // 1 = Pressed,2 <= Held
    int push_time_squat_;      // 1 = Pressed,2 <= Held

    void fireMove();           // ファイアボールを投げる動き
};