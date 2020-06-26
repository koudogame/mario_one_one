#pragma once 
#include "base_scene.hpp"
#include "field.hpp"
#include "player.hpp"
#include "item.hpp"
#include "enemy.hpp"
#include "pos_collision.hpp"

class PlayScene :
    public BaseScene
{
public :
    PlayScene();
    ~PlayScene();

    bool initialize() override;    
    void update() override;
    void draw() override;
    void finalize() override;

private:   
    Item* item_;
    Field* field_;
    Player* player_;
    Enemy* enemy_;
    PosCollision* pos_col_;
};