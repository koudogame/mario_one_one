#pragma once
#include <vector>
#include <fstream>
#include "enemy_base.hpp"
#include "release.hpp"
#include "field.hpp"

/*NewするClass*/
#include "kuribo.hpp"    
#include "turtle.hpp"

const int kKuribo = 0;
const int kTurtle = 36;
const int kSize   = 64;
const int kShell  = 113;

class Enemy
{
public :

    Enemy( Field* Field );
    void initalize( std::fstream& FieldEnemy );
    void update( int ScreenOver );
    void draw( int ScreenOver );
    void finalize();

    void posCollision( int i, int j, int Touch );
    void shellCollision( int i, int j );
    void fireCollision( int i, int j );
    void changeDirection( int i, int j );

    inline bool getPushFlag( int i, int j ) { return enemy_[ 0 ][ i ][ j ]->getPushFlag(); }
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

    // マップチップ
    std::vector<std::vector<std::vector<EnemyBase*>>> enemy_;
};