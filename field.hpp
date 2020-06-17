#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"
#include "both_hands.hpp"
#include "release.hpp"


class Field
{
public :
    bool initialize(std::fstream& stage);
    void update();
    void draw(int ScreenOver);
    void finalize();

    // �̂̉E��
    int getRightShoulderId( Side side_ );
    int getRightHandId( Side side_ );
    // �̂̍���
    int getLeftShoulderId( Side side_ );
    int getLeftHandId( Side side_ );

private :
    Side side_;

    int texture_;              // �e�N�X�`���n���h���ۑ��p
    int height_;               // ����
    int width_;                // ����

    // ������ݒ肵�Ȃ��Ă�������z��
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};