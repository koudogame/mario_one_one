#pragma once
#include <vector>
#include <fstream>
#include "enemy_base.hpp"
#include "release.hpp"
#include "field.hpp"

/*New����Class*/
#include "kuribo.hpp"    

const int kKuribo = 0;
const int kSize = 64;

class Enemy
{
public :

    Enemy( Field* Field );
    void initalize( std::fstream& FieldEnemy );
    void update( int ScreenOver );
    void draw( int ScreenOver );
    void finalize();

    void posCollision( int i, int j );

    inline int getEnemyPosX( int i, int j ) { return enemy_[ 0 ][ i ][ j ]->getPosX(); }
    inline int getEnemyPosY( int i, int j ) { return enemy_[ 0 ][ i ][ j ]->getPosY(); }
    inline int getWidth() { return width_; }
    inline int getHeight() { return height_; }
    inline int getId( int i, int j ) { return enemy_[ 0 ][ i ][ j ]->getId(); }

private : 
    Field* field_;

    int texture_;
    int width_;
    int height_;

    // �}�b�v�`�b�v
    std::vector<std::vector<std::vector<EnemyBase*>>> enemy_;
};