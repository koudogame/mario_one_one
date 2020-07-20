#include <Dxlib.h>
#include "collision.hpp"

class FireFactory :
    public Collision
{
public :
    const int kGravity     = 1;
    const int kSmall       = 6;
    const int kBic         = 12;
    const int kAnime       = 8;
    const int kSpeed       = 12;
    const int kJumpPower   = 4;
    const int kGround      = 575;
    const int kScreenXSize = 1280;
    const int kScreenYSize = 720;

    FireFactory( Field* field ) : Collision( field ) {};
    void initialize( int, int, int );
    void update();
    void draw(int , const int );

    bool getCheckScreen(const int);    
    void animation();           // アニメーションする関数
    void burnAnimation();       // 爆発アニメーション関数
    void setFire(bool);         
    
    inline bool getExplode() { return explode_flag_; }

    inline int getFirePosX() { return fire_pos_x_; }
    inline int getFirePosY() { return fire_pos_y_; }


private : 
    bool side_touch_;           // 横から当たったか調べる
    int texture_;               // 引数で受け取った画像を保存
    int direction_;             // 最初に受け取った向きを保存

    int animation_cnt_;         // if文判定用
    int animation_;             // 数値によって回転する
    int fire_pos_x_;            // 引数で受け取ったPosXを保存
    int fire_pos_y_;            // 引数で受け取ったPosYを保存

    int explosion_[ 4 ] = { 0 };// 爆破演出Rect
    int explode_cnt_;
    int explode_flag_;
};

// fire_factoryは作られる側なので共通した処理を書き込む。
// 例）衝突判定、描画関係、アニメーション等。