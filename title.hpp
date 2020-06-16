#pragma once

#include "base_scene.hpp"

class TitleScene :
    public BaseScene
{
public:
    bool initialize() override;
    void update() override;
    void draw() override;
    void finalize() override;

private:
};