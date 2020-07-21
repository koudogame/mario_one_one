#pragma once
#include <vector>
#include <fstream>
#include "item_base.hpp"
#include "release.hpp"
#include "field.hpp"

/* New����Class */
#include "coin.hpp"
#include "power_up.hpp"
#include "goal.hpp"
#include "castle_flag.hpp"


class Item
{
public:
    const int kFlag     = 3;        // ��ID
    const int kPowerup  = 0;        // �L�m�RID
    const int kPowerup2 = 16;       // �t�����[ID
    const int kGoal     = 19;       // �S�[��ID
    const int kCoin     = 80;       // �R�C��ID
    const int kItemsize = 64;       // �A�C�e���̑傫��

    Item( Field* Field );
    bool initialize( std::fstream& stage );
    void update( int Brx, int Bry, int Blx, int Bly, int Status, int Screenover );
    void draw( int Screenover );
    void finalize();

    void posCollision( int i, int j );      // �}���I�Ɠ��������Ƃ��ɌĂ΂��֐�
    void getGoal( bool );
    void getEnd( bool );

    inline int getItemPosX( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosX(); }
    inline int getItemPosY( int i, int j ) { return item_[ 0 ][ i ][ j ]->getPosY(); }
    inline int getWidth() { return width_; }
    inline int getHeight() { return height_; }
    inline int getId( int i, int j ) { return item_[ 0 ][ i ][ j ]->getId(); }

private:
    Field* field_;

    int texture_;       // �e�N�X�`���n���h���ۑ��p
    int width_;         // ����
    int height_;        // ����

    // �}�b�v�`�b�v�z��
    std::vector<std::vector<std::vector<ItemBase*>>> item_;
};