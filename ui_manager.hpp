#pragma once

/*New����Class*/
#include "ui_map.hpp"


class UIManager
{
public:
    void initialize();
    void update();
    void draw();
    void finalize();

private:
    int texture_;   // �e�N�X�`��
    UIMap map_;     // Map�̊Ǘ�
};