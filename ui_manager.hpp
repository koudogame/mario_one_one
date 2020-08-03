#pragma once

/*New����Class*/
#include "ui_map.hpp"
#include "ui_coin.hpp"
#include "ui_time.hpp"
#include "ui_score.hpp"

class UIManager
{
public:
    void initialize();
    void update( bool );
    void draw();
    void finalize();

    // ���Ԃ��󂯎��X�R�A�ɕϊ�����
    void timeScore();

    // ��������R�C�������`��
    void coinCheck( int );
    
    // ���ԓ������ԊO��`����
    inline bool timeLimit() { return time_.timeLimit(); }

    // �c�莞�Ԃ�`����
    inline int getTime() { return time_.getTime(); }

private:
    int texture_;     // �e�N�X�`��
    UIMap map_;       // Map�̊Ǘ�
    UICoin coin_;     // Coin�̊Ǘ�
    UITime time_;     // Time�̊Ǘ�
    UIScore score_;   // Score�̊Ǘ�
};