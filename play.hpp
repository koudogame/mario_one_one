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
    const int kChangeTime = 120;

    PlayScene();
    ~PlayScene();

    bool initialize() override;    
    void update() override;
    void draw() override;
    void finalize() override;

private:   
    Item* item_;            // �A�C�e���N���X
    Field* field_;          // �t�B�[���h�N���X
    Player* player_;        // �v���C���[�N���X
    Enemy* enemy_;          // �G�l�~�[�N���X
    BallManagement* bm_;    // �{�[���}�l�[�W���[�N���X
    PosCollision* pos_col_; // �|�W�V�����Փ˔���N���X

    int touch_;
    int change_timer_;
};