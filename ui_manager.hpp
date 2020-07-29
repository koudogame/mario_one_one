#pragma once

/*New����Class*/
#include "ui_map.hpp"
#include "ui_coin.hpp"
#include "ui_time.hpp"

class UIManager
{
public:
    void initialize();
    void update( bool );
    void draw();
    void finalize();

    void coinCheck( int );
    
    // ���ԓ������ԊO��`����
    inline bool timeLimit() { return time_.timeLimit(); }

private:
    int texture_;   // �e�N�X�`��
    UIMap map_;     // Map�̊Ǘ�
    UICoin coin_;   // Coin�̊Ǘ�
    UITime time_;   // Time�̊Ǘ�
};