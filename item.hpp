#pragma once
#include <vector>
#include <fstream>
#include "item_base.hpp"
#include "release.hpp"
#include "field.hpp"

/* New����Class */
#include "coin.hpp"

constexpr int kCoin = 48;
constexpr int kItemsize = 64;

/* New����Class */

class Item
{
public :
    Item( Field* Field );
    bool initialize( std::fstream& stage );
    void update( int Brx, int Bry, int Blx, int Bly, int Status );
    void draw( int Screenover );
    void finalize();

private :  
    Field* field_;

    int texture_;       // �e�N�X�`���n���h���ۑ��p
    int height_;        // ����
    int width_;         // ����

    // �}�b�v�`�b�v�z��
    std::vector<std::vector<std::vector<ItemBase*>>> item_;
};