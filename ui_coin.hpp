#pragma once
#include "ui_base.hpp"

/* �ꌅ�� A, �񌅖� B�ƕ\�� */

class UICoin :
    public UIBase
{
public:
    const int kDigitArray = 2;                                 // �g�p���錅��
    const int kCoinNum    = 2;                                 // �R�C���̍��[
    const int kTimesNum   = 10;                                // �~�̔ԍ� 
    const int kStartPos   = 424;                               // A�̃|�W�V����
    const int kTimes      = kStartPos - kHalfSize;             // �~�̃|�W�V���� 
    const int kCoinPosX   = kTimes - kHalfSize - kQuarterSize; // �R�C���̃|�W�V����

    void initialize() override;
    void update() override;
    void draw(int) override;
    void finalize() override;

    void coinCounter( int ); // �@���ꂽ�������擾

private:
    int item_texture_;       // �A�C�e���e�N�X�`��
};