#pragma once 

class DataKeeper
{
public:
    void setResidue( int Residue ) { residue_ = Residue; }             // �c���ۑ�������֐�
    inline int getResidue() { return residue_; }                       // �c��̐���m�邽�߂̊֐�

    void setCoin( int Coin ) { coin_ = Coin; }                         // �R�C���̐���ۑ�������֐�
    inline int getCoin() { return coin_; }                             // �R�C���̐���m�邽�߂̊֐�

private : 
    int residue_ = 3;   // �ŏ��̂ݎc��w��
    int coin_ = 0;      // ������
};