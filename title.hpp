#pragma once

#include "base_scene.hpp"

class TitleScene :
    public BaseScene
{
public:
    bool initialize() override;
    void finalize() override;
    void update() override;  

private:
};