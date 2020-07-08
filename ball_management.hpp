#pragma once
#include<DxLib.h>
#include "fire_factory.hpp"
#include "collision.hpp"

class BallManagement
{
public :
    BallManagement( Field* field ) : ff_( field ) { field_ = field; }

    void initialize();
    void update( int, int, int, int ); // position_x_, position_y_, status_, direction_;
    void draw(const int);              // ScreenOver
    void finalize();

    int getFirePosX(int);              // fire��X���W��Ԃ�
    int getFirePosY(int);              // fire��Y���W��Ԃ�

    int getSize();                     // for���p�ɃT�C�Y��Ԃ�

private: 
    Field* field_;
    FireFactory ff_;

    int texture_;

    // �S�̃t�@�C�A�Ǘ��p�z��
    std::vector<FireFactory*> fire_;
};

// fire_factory�����ׂē������ĊǗ�����̂ł��ׂĂ𑀍삷��K�v������B