#include "field.hpp"
#include "both_hands.hpp"
#include "up_and_down.hpp"
#include "release.hpp"

constexpr int kSize        = 64;
constexpr int kSpeed       = 6;
constexpr int kJumpPower   = 25;
constexpr int kStartX      = 256;
constexpr int kStartY      = 576;
constexpr int kEndLine     = 576;
constexpr int kDeadLine    = 704;
constexpr int kSkyBlue     = 191;
constexpr int kGravity     = 1;

// マリオの状態保存
enum Status
{
    kMario = 0,
    kSuperMario,
    kFireMario
};

class Player
{
public:
    Player(Field* Field);
    ~Player();
    bool initialize();
    void update();
    void draw();
    void finalize();

    void animation();          // マリオのアニメーション
    void collision();          // 足元の衝突判定を行う
    void landing();            // 着地したときの処理を行う
    void hit();                // 頭をぶつけたときの判定

    inline Side getSide() { return side_; }         // 体の左右
    inline UpDown getUpDown() { return updown_; }   // 体の上下

    /*背景の描画を流す数値*/
    inline int getScrollCnt() { return scroll_cnt_; }                

private:
    Side side_;                // Side構造体を持つ
    UpDown updown_;            // UpDown構造体を持つ

    Field* field_;             // Fieldの関数が使えるようにする

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

    int scroll_cnt_;           // 半分をマリオが超えたときにスクロール

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

    int acceleration_;         // ジャンプ力を付与
    bool jumping_;             // true : 飛べる, false : 飛べない

    int break_right_x_;        // 右頭のぶつかった座標x
    int break_right_y_;        // 右頭のぶつかった座標y

    int break_left_x_;         // 左頭のぶつかった座標x
    int break_left_y_;         // 左頭のぶつかった座標y
};