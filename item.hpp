#pragma once
#include <vector>
#include <fstream>
#include "item_base.hpp"
#include "release.hpp"
#include "field.hpp"

/* New����Class */
#include "coin.hpp"
#include "power_up.hpp"

constexpr int kPowerup  = 0;
constexpr int kPowerup2 = 16;
constexpr int kCoin     = 48;
constexpr int kItemsize = 64;

/* New����Class */

class Item
{
public :
    Item( Field* Field );
    bool initialize( std::fstream& stage );
    void update( int Brx, int Bry, int Blx, int Bly, int Status, int Screenover );
    void draw( int Screenover );
    void finalize();

    int getItemPosX( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosX(); }
    int getItemPosY( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosY(); }

    int getWidth() { return width_; }
    int getHeight() { return height_; }

    int getID( int i, int j ) { return item_[ 0 ][ i ][ j ]->getId(); }
    void posCollision( int i, int j );

private :  
    Field* field_;

    int texture_;       // �e�N�X�`���n���h���ۑ��p
    int height_;        // ����
    int width_;         // ����
    
    // �}�b�v�`�b�v�z��
    std::vector<std::vector<std::vector<ItemBase*>>> item_;
};