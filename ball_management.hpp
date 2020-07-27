#pragma once
#include "fire_factory.hpp"
#include "collision.hpp"

class BallManagement
{
public :
    const int kBallLimit = 4;    // �A���ŏo���鐔��ݒ�
    const int kStopper   = 16;   // �A�˖h�~���l
    const int kEndline   = 640;  // �s���Ă͂����Ȃ����W

    BallManagement( Field* field ) : ff_( field ) { field_ = field; }

    void initialize();
    void update( int, int, int, int, bool ,int);
    void draw(const int);              // ScreenOver
    void finalize();

    void createFire(int, int, int, int);
    void sideCheck();
    void posCheck(const int);          // �t�@�C�A�{�[���̏ꏊ���`�F�b�N����
    void enemyCollision( int );        // ���������Ƃ��̉΂�����

    int getFirePosX(int);              // fire��X���W��Ԃ�
    int getFirePosY(int);              // fire��Y���W��Ԃ�

    int getSize();                     // for���p�ɃT�C�Y��Ԃ�

private: 

    Field* field_;
    FireFactory ff_;

    int texture_;
    int push_create_fire_;             // �P�������ł���悤���ԊǗ�

    int create_cnt_;                   // ���񐶐��܂ł̎��Ԍv��
    bool create_flag_;                 // �����؂�ւ�

    // �S�̃t�@�C�A�Ǘ��p�z��
    std::vector<FireFactory*> fire_;
};

// fire_factory�����ׂē������ĊǗ�����̂ł��ׂĂ𑀍삷��K�v������B