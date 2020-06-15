#pragma once 
#include "base_scene.hpp"

// ‚±‚±‚ÉŒã‚©‚çField, Player‚ð‚©‚±‚¤

class PlayScene :
    public BaseScene
{
public :
    bool initialize() override;
    void finalize() override;
    void update() override;

private:
};