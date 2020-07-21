#pragma once
#include <vector>
#include <fstream>
#include "enemy_base.hpp"
#include "release.hpp"
#include "field.hpp"

/*New����Class*/
#include "kuribo.hpp"    
#include "turtle.hpp"


class Enemy
{
public:
    const int kKuribo = 0;      // �N���{�[ID
    const int kTurtle = 36;     // �m�R�m�RID
    const int kSize   = 64;     // �G�̑傫��
    const int kShell  = 113;    // �������ID 

    Enemy( Field* Field );
    void initalize( std::fstream& FieldEnemy );
    void update( int ScreenOver );
    void draw( int ScreenOver );
    void finalize();

    void posCollision( int i, int j, int Touch );   // �|�W�V������񂪃}���I�Ɠ��������Ƃ��ɌĂ΂��֐�
    void shellCollision( int i, int j );            // �b����ԂŏՓ˂����Ƃ��ɌĂ΂��֐�
    void fireCollision( int i, int j );             // �t�@�C�A�{�[���ƏՓ˂����Ƃ��ɌĂ΂��֐�
    void changeDirection( int i, int j );           // �|�W�V�������Ԃ��������ύX����Ƃ��ɌĂ΂��֐�

    inline bool getPushFlag( int i, int j ) { return enemy_[ 0 ][ i ][ j ]->getPushFlag(); }
    inline int getEnemyPosX( int i, int j ) { return enemy_[ 0 ][ i ][ j ]->getPosX(); }
    inline int getEnemyPosY( int i, int j ) { return enemy_[ 0 ][ i ][ j ]->getPosY(); }
    inline int getWidth() { return width_; }
    inline int getHeight() { return height_; }
    inline int getId( int i, int j ) { return enemy_[ 0 ][ i ][ j ]->getId(); }

private:
    Field* field_;

    int texture_;
    int width_;
    int height_;

    // �}�b�v�`�b�v
    std::vector<std::vector<std::vector<EnemyBase*>>> enemy_;
};