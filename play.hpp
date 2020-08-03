#pragma once 
#include "base_scene.hpp"
#include "field.hpp"
#include "player.hpp"
#include "item.hpp"
#include "enemy.hpp"
#include "goal_fire.hpp"
#include "ui_manager.hpp"
#include "ball_management.hpp"
#include "pos_collision.hpp"

class PlayScene :
    public BaseScene
{
public :
    const int kChangeTime = 120;// シーンチェンジカウント

    PlayScene();
    ~PlayScene();

    bool initialize() override;    
    void update() override;
    void draw() override;
    void finalize() override;

private:   
    Item* item_;                // アイテムクラス
    Field* field_;              // フィールドクラス
    Player* player_;            // プレイヤークラス
    Enemy* enemy_;              // エネミークラス
    GoalFire* gf_;              // ゴール後花火クラス
    UIManager* ui_;             // UIクラス
    BallManagement* bm_;        // ボールマネージャークラス
    PosCollision* pos_col_;     // ポジション衝突判定クラス

    int touch_;
    int clear_num_;
    int change_timer_;

    void resultScene();         // リザルトシーンへ遷移
};