#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"

class Field
{
public :
    bool initialize(std::fstream& stage);
    void update(int Texture, int ScreenOver);
    void finalize();

private :
    int texture_;              // �e�N�X�`���n���h���ۑ��p
    int height_;               // ����
    int width_;                // ����

    // ������ݒ肵�Ȃ��Ă�������z��
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};