#pragma once

/*New����Class*/
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
    int texture_;   // �e�N�X�`��
    UIMap map_;     // Map�̊Ǘ�
    UICoin coin_;   // Coin�̊Ǘ�
};