#pragma once

/*NewするClass*/
#include "ui_map.hpp"


class UIManager
{
public:
    void initialize();
    void update();
    void draw();
    void finalize();

private:
    int texture_;   // テクスチャ
    UIMap map_;     // Mapの管理
};