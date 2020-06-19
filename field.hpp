#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"
#include "both_hands.hpp"
#include "up_and_down.hpp"
#include "release.hpp"

/* New����Class */
#include "mystery.hpp"

constexpr int kMystery = 48;


class Field
{
public :
    bool initialize(std::fstream& stage);
    void update( int Brx, int Bry, int Blx, int Bly );
    void draw(int ScreenOver);
    void finalize();

    // �̂̉E��
    int getRightShoulderId( Side side_ );
    int getRightHandId    ( Side side_ );
    // �̂̍���
    int getLeftShoulderId ( Side side_ );
    int getLeftHandId     ( Side side_ );
    // �̂̏㑤
    int getRightHeadId    ( UpDown updown_ );
    int getLeftHeadId     ( UpDown updown_ );
    // �̂̉���
    int getRightFootId    ( UpDown updown_ );
    int getLeftFootId     ( UpDown updown_ );

private :
    Side side_;                // Side�\����
    UpDown updown_;            // UpDown�\����

    int texture_;              // �e�N�X�`���n���h���ۑ��p
    int height_;               // ����
    int width_;                // ����

    // ������ݒ肵�Ȃ��Ă�������z��
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};