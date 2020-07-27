#pragma once 
#include "enemy_base.hpp"

class Kuribo :
    public EnemyBase
{
public :
    const int kDown        = 5;        // �����Ă���
    const int kDeathTime   = 32;       // ��ʂ��������܂ł̃��~�b�g
    const int kDead        = 112;      // ���񂾂Ƃ�
    const int kFieldSize   = 800;      // ���̌��E�l

    Kuribo( Field* Field ) : EnemyBase( Field ) {};
    void update( int ScreenOver )override;
    
    int getPosX() override;
    int getPosY() override;

    void posCollision(int Touch) override;  // �}���I�Ƃ̏Փ˂��������Ƃ�
    void animation();                       // �����A�j���[�V����

private : 
    int death_cnt_       = 0;               // ������܂ł̃J�E���g�_�E��
    bool move_start_     = true;            // true : �����Ȃ�, false : �����o��
    bool alive_          = true;            // true : �����Ă���, false : ����ł���
};