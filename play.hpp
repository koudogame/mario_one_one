#pragma once 
#include "base_scene.hpp"

// ここに後からField, Playerをかこう

class PlayScene :
    public BaseScene
{
public :
    bool initialize() override;
    void finalize() override;
    void update() override;

private:
};