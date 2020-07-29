#pragma once
#include "ui_base.hpp"

/* �ꌅ�� A, �񌅖� B�ƕ\�� */

class UICoin :
    public UIBase
{
public:
    const int kCoinNum  = 2;      // �R�C���̍��[
    const int kTimesNum = 10;     // �~�̔ԍ� 
    const int kCountUp  = 10;     // �J�E���g�A�b�v
    const int kCoinPosX = 434;    // �R�C���̃|�W�V����
    const int kTimes    = 492;    // �~�̃|�W�V���� 
    const int kNumPosBX = 534;    // B�̃|�W�V����
    const int kNumPosAX = 576;    // A�̃|�W�V����

    void initialize() override;
    void update() override;
    void draw(int) override;
    void finalize() override;

    void coinCounter( int );      // �@���ꂽ�������擾

private:
    int item_texture_;            // �A�C�e���e�N�X�`��
};