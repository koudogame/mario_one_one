#pragma once

/*NewするClass*/
#include "ui_map.hpp"
#include "ui_coin.hpp"

class UIManager
{
public:
    void initialize();
    void update();
    void draw();
    void finalize();

    void coinCheck( int );

private:
    int texture_;   // テクスチャ
    UIMap map_;     // Mapの管理
    UICoin coin_;   // Coinの管理
};