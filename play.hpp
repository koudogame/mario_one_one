#pragma once 
#include "base_scene.hpp"
#include "field.hpp"
#include "player.hpp"


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
    Field* field_;
    Player* player_;
};