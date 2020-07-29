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
    const int kCoinPosX = 472;    // �R�C���̃|�W�V����
    const int kTimes    = 514;    // �~�̃|�W�V���� 
    const int kNumPosBX = 556;    // B�̃|�W�V����
    const int kNumPosAX = 598;    // A�̃|�W�V����

    void initialize() override;
    void update() override;
    void draw(int) override;
    void finalize() override;

    void coinCounter( int );      // �@���ꂽ�������擾

private:
    int item_texture_;            // �A�C�e���e�N�X�`��
};