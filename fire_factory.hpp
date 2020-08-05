#include "collision.hpp"

class FireFactory :
    public Collision
{
public :
    const int kJumpPower   = 8;     // ジャンプ力
    const int kLimit       = 4;     // アニメ切り替え
    const int kAnime       = 8;     // アニメーション
    const int kSpeed       = 16;    // ファイア移動速度
    const int kGround      = 575;   // 地面
    const int kScreenXSize = 1280;  // X軸上限
    const int kScreenYSize = 720;   // Y軸上限

    FireFactory( Field* field ) : Collision( field ) {};
    void initialize( int, int, int );
    void update();
    void draw(int , const int );

    bool getCheckScreen(const int);    
    void animation();               // アニメーションする関数
    void burnAnimation();           // 爆発アニメーション関数
    void setFire(bool);         
    
    inline bool getExplode() { return explode_flag_; }

    inline int getFirePosX() { return fire_position_.x; }
    inline int getFirePosY() { return fire_position_.y; }


private : 
    Rect<int> rect_;                // Rectを用意
    Position<int> fire_position_;   // Positionを用意 

    bool side_touch_;               // 横から当たったか調べる
    int texture_;                   // 引数で受け取った画像を保存
    int direction_;                 // 最初に受け取った向きを保存

    int animation_cnt_;             // if文判定用
    int animation_;                 // 数値によって回転する

    int explode_cnt_;
    int explode_flag_;
};

// fire_factoryは作られる側なので共通した処理を書き込む。
// 例）衝突判定、描画関係、アニメーション等。