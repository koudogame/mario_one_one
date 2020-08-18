#include "collision.hpp"
#include "namespace.hpp"

class Player :
    public Collision
{
public:
    const int kSliding    = 5;   // スライディングアニメ 
    const int kSpeed      = 6;   // 歩いているときの速度
    const int kDownSpeed  = 6;   // ゴールしたとき落ちるスピード
    const int kAnimeMove  = 8;   // アニメーション用
    const int kEnemyJump  = 8;   // 敵を踏んだ時のジャンプ力
    const int kDashSpeed  = 10;  // ダッシュしているときの速度
    const int kStopper    = 16;  // 連射防止ストッパー
    const int kJumpPower  = 24;  // ジャンプボタン時のジャンプ力
    const int kDownCnt    = 66;  // 掴んでからの待ち時間
    const int kTurnCnt    = 90;  // 向き反転させるための時間
    const int kInvincible = 180; // 無敵制限時間
    const int kSkyBlue    = 191; // 背景の何もない透明マップチップID
    const int kGoalPost   = 194; // ゴールポスト
    const int kEntrance   = 201; // 塔の入り口
    const int kStartX     = 256; // 初期座標X
    const int kStartY     = 576; // 初期座標Y
    const int kEndLine    = 576; // 画面の中心
    const int kDeadLine   = 800; // この数値より下は死ぬ

    PlayerData getData();

    Player( Field* field ) : Collision( field ) {};
    bool initialize();
    bool update(bool);
    void draw();
    void finalize();

    void animation();            // マリオのアニメーション
    void collision();            // 足元の衝突判定を行う
    void landing();              // 着地したときの処理を行う
    void hit();                  // 頭をぶつけたときの判定
    void itemCollision();        // アイテムに当たったとき
    void enemyCollision();       // ぶつかったときの処理
    void enemyStepon();          // 踏みつけたときの処理      
    void ending();               // エンディング処理
    void rightCheck();           // 体の右側を登録してチェックする関数
    void leftCheck();            // 体の左側を登録してチェックする関数

    inline bool getInvincibleTime() { return invincible_time_; }

    // 向きに応じて渡す
    inline int getDirection() 
    {
        if( direction_ ) return 1;
        else return -1;
    }
    
private:
    PlayerData data_;               // データ受け渡し用変数

    Rect<int> rect_;                // Rect呼び出し
    Position<int> position_;        // Position呼び出し
    Position<int> total_move_;      // Position呼び出し
    Position<int> break_right_;     // 頭の右の座標
    Position<int> break_left_;      // 頭の左の座標
                                    
    int texture_;                   // テクスチャハンドル
    int past_status_;               // マリオの過去の状態
                                                                                                            
    int animation_;                 // 動いているときの切り取り範囲
    bool direction_;                // true : 右向き, false : 左向き
                                    
    int animation_cnt_;             // 動かすためのアニメーション速さ調整 
    bool animation_flag_;           // true : 動く, false : 動かない
                                    
    bool old_right_button_;         // true : 押してない, false : 押しています
    bool old_left_button_;          // true : 押してない, false : 押しています
    bool old_down_button_;          // true : 押してない, false : 押しています
                                    
    bool right_button_;             // true : 押してない, false : 押しています 
    bool left_button_;              // true : 押してない, false : 押しています
                                    
    int invincible_cnt_;            // 無敵時間の計測
    bool invincible_time_;          // 無敵だが動ける時間
                                    
    bool catch_flag_;               // true : 掴まっていない, false : 掴んでいる
                                    
    int down_cnt_;                  // この値が66になったら向き反転
    int throw_cnt_;                 // 投げるモーションの維持
    bool throw_flag_;               // 投げるモーションの維持
                                    
    int push_time_jump_;            // 1 = Pressed,2 <= Held
    int push_time_fire_;            // 1 = Pressed,2 <= Held
    int push_time_run_;             // 1 = Pressed,2 <= Held
    int timekeep_squat_;            // 1 = Pressed,2 <= Held
                                    
    int speed_;                     // 加速度
    int speed_up_;                  // 数フレームで１回加速を行う
    int speed_down_;                // 数フレームで１回減速を行う
    bool sliding_;                  // true : 滑っている, false : 滑っていない
                                    
    void squat();                   // しゃがむ動作を行う関数
    void fireMove();                // ファイアボールを投げる動き
    void defaultSize( int Status ); // 引数でrect_を調整する関数

    void rightPush();               // 右を押した時の処理
    void leftPush();                // 左を押した時の処理
};