#pragma once
#include "ui_base.hpp"

/* �ꌅ�� A, �񌅖� B�ƕ\�� */

class UICoin :
    public UIBase
{
public:
    const int kCoinNum  = 2;                                 // �R�C���̍��[
    const int kTimesNum = 10;                                // �~�̔ԍ� 
    const int kCountUp  = 10;                                // �J�E���g�A�b�v
    const int kNumPosAX = 424;                               // A�̃|�W�V����
    const int kNumPosBX = kNumPosAX - kQuarterSize;          // B�̃|�W�V����
    const int kTimes    = kNumPosBX - kQuarterSize;          // �~�̃|�W�V���� 
    const int kCoinPosX = kTimes - kHalfSize - kQuarterSize; // �R�C���̃|�W�V����

    void initialize() override;
    void update() override;
    void draw(int) override;
    void finalize() override;

    void coinCounter( int ); // �@���ꂽ�������擾

private:
    int item_texture_;       // �A�C�e���e�N�X�`��
};