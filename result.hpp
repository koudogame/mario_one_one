#pragma once 
#include <DxLib.h>
#include "base_scene.hpp"
#include "data_keeper.hpp"

class ResultScene :
    public BaseScene
{
public :
    bool initialize() override;
    void update() override;
    void draw() override;
    void finalize() override;

private:
    DataKeeper* data_;
    int texture_;

    int push_time_go_;      // Bƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½‚Æ‚«
};