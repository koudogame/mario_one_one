#pragma once 
#include "base_scene.hpp"
#include "field.hpp"
#include "player.hpp"
#include "item.hpp"
#include "enemy.hpp"
#include "ball_management.hpp"
#include "pos_collision.hpp"

class PlayScene :
    public BaseScene
{
public :
    const int kKuribo     = 0;
    const int kTurtle     = 36;
    const int kShell      = 113;
    const int kPowerup    = 0;
    const int kPowerup2   = 16;
    const int kChangeTime = 120;

    PlayScene();
    ~PlayScene();

    bool initialize() override;    
    void update() override;
    void draw() override;
    void finalize() override;

private:   
    Item* item_;            // アイテムクラス
    Field* field_;          // フィールドクラス
    Player* player_;        // プレイヤークラス
    Enemy* enemy_;          // エネミークラス
    BallManagement* bm_;    // ボールマネージャークラス
    PosCollision* pos_col_; // ポジション衝突判定クラス

    int touch_;
    int change_timer_;
};