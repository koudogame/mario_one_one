#pragma once
#include "block_base.hpp"
#include "release.hpp"
#include "namespace.hpp"

/* New����Class */
#include "mystery.hpp"
#include "brick.hpp"

const int kNoblock = 190; // �����Ȃ��u���b�NID


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
    void update( PlayerData );
    void draw(int ScreenOver);
    void drawFront( int ScreenOver );
    void finalize();

    // �@���ꂽ�u���b�N���グ��������֐�
    void downBlock();

    // �̂̃}�b�vId��Ԃ��O�����z��
    int getId( int PosX, int PosY );

private :
    Position<int> block_right_;
    Position<int> block_left_;

    int texture_;              // �e�N�X�`���n���h���ۑ��p
    int height_;               // ����
    int width_;                // ����

    // ������ݒ肵�Ȃ��Ă�������z��
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};