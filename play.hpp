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
    const int kChangeTime = 120;// �V�[���`�F���W�J�E���g

    PlayScene();
    ~PlayScene();

    bool initialize() override;    
    void update() override;
    void draw() override;
    void finalize() override;

private:   
    Item* item_;                // �A�C�e���N���X
    Field* field_;              // �t�B�[���h�N���X
    Player* player_;            // �v���C���[�N���X
    Enemy* enemy_;              // �G�l�~�[�N���X
    GoalFire* gf_;              // �S�[����ԉ΃N���X
    UIManager* ui_;             // UI�N���X
    BallManagement* bm_;        // �{�[���}�l�[�W���[�N���X
    PosCollision* pos_col_;     // �|�W�V�����Փ˔���N���X

    int touch_;
    int clear_num_;
    int change_timer_;

    void resultScene();         // ���U���g�V�[���֑J��
};