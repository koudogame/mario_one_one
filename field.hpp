#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"
#include "release.hpp"

/* New����Class */
#include "mystery.hpp"
#include "brick.hpp"

static const int kLength    = 16;       // �z��̉��̒���
static const int kBrick     = 19;       // �����K�u���b�NID
static const int kMystery   = 48;       // �͂Ăȃ{�b�N�XID
static const int kNoblock   = 190;      // �����Ȃ��u���b�NID


namespace breakblock
{
    enum BreakParts
    {
        kRightUp, kRightDown, kLeftUp, kLeftDown, kBreakParts
    };

    enum Vector2
    {
        kPositionX, kPositionY, kVector2
    };
}

using namespace breakblock;

class Field
{
public :
    bool initialize(std::fstream& stage);
    void update( int Brx, int Bry, int Blx, int Bly , int Status);
    void draw(int ScreenOver);
    void drawFront( int ScreenOver );
    void finalize();

    // �@���ꂽ�u���b�N���グ��������֐�
    void downBlock();

    // �̂̃}�b�vId��Ԃ��O�����z��
    int getId( int PosX, int PosY );

private :
    int texture_;              // �e�N�X�`���n���h���ۑ��p
    int height_;               // ����
    int width_;                // ����
    int block_rx_;             // ���dupdate��h������
    int block_ry_;             // ���dupdate��h������
    int block_lx_;             // ���dupdate��h������
    int block_ly_;             // ���dupdate��h������

                               // ������ݒ肵�Ȃ��Ă�������z��
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};