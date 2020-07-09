#pragma once
#include<DxLib.h>
#include "fire_factory.hpp"
#include "collision.hpp"

class BallManagement
{
public :
    BallManagement( Field* field ) : ff_( field ) { field_ = field; }

    void initialize();
    void update( int, int, int, int, bool ); // position_x_, position_y_, status_, direction_, gameoverflag;
    void draw(const int);              // ScreenOver
    void finalize();

    void posCheck(const int);                   // �t�@�C�A�{�[���̏ꏊ���`�F�b�N����
    void enemyCollision( int );        // ���������Ƃ��̉΂�����

    int getFirePosX(int);              // fire��X���W��Ԃ�
    int getFirePosY(int);              // fire��Y���W��Ԃ�

    int getSize();                     // for���p�ɃT�C�Y��Ԃ�

private: 

    Field* field_;
    FireFactory ff_;

    int texture_;
    int push_create_fire_;             // �P�������ł���悤���ԊǗ�

    // �S�̃t�@�C�A�Ǘ��p�z��
    std::vector<FireFactory*> fire_;
};

// fire_factory�����ׂē������ĊǗ�����̂ł��ׂĂ𑀍삷��K�v������B