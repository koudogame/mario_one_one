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

enum RL
{
    kRight, kLeft, kRL
};

enum BodyParts
{
    kShoulder, kHands, kHead, kFoot, kBodyParts
};

enum Position
{
    kX, kY, kPosition
};

class Field
{
public :
    bool initialize(std::fstream& stage);
    void update( int Brx, int Bry, int Blx, int Bly , int Status);
    void draw(int ScreenOver);
    void finalize();

    // �̂̃|�W�V�������Z�b�g����֐�
    void setPosition(RL rl, BodyParts parts, Position position, int Movement);

    // �̂̃}�b�vId��Ԃ��O�����z��
    int getPoint(RL rl, BodyParts parts);

private :
    int  bodyId_[kRL][kBodyParts][kPosition];

    int texture_;              // �e�N�X�`���n���h���ۑ��p
    int height_;               // ����
    int width_;                // ����

    // ������ݒ肵�Ȃ��Ă�������z��
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};