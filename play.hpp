#pragma once 
#include "base_scene.hpp"

// �����Ɍォ��Field, Player��������

class PlayScene :
    public BaseScene
{
public :
    bool initialize() override;
    void finalize() override;
    void update() override;

private:
};