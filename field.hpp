#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"
#include "release.hpp"

/* New����Class */
#include "mystery.hpp"
#include "brick.hpp"

constexpr int kBrick = 19;
constexpr int kMystery = 48;

class Field
{
public :
    bool initialize(std::fstream& stage);
    void update( int Brx, int Bry, int Blx, int Bly , int Status);
    void draw(int ScreenOver);
    void finalize();

    void downBlock();

    // �̂̃}�b�vId��Ԃ��O�����z��
    int getId( int PosX, int PosY );

private :
    int texture_;              // �e�N�X�`���n���h���ۑ��p
    int height_;               // ����
    int width_;                // ����

    // ������ݒ肵�Ȃ��Ă�������z��
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};