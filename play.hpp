#pragma once 
#include "base_scene.hpp"

// �����Ɍォ��Field, Player��������
#include "field.hpp"


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
};