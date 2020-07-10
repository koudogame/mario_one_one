#pragma once 

class DataKeeper
{
public:
    void setResidue( int Residue ) { residue_ = Residue; }             // 残基を保存させる関数
    inline int getResidue() { return residue_; }                       // 残基の数を知るための関数

    void setCoin( int Coin ) { coin_ = Coin; }                         // コインの数を保存させる関数
    inline int getCoin() { return coin_; }                             // コインの数を知るための関数

private : 
    int residue_ = 3;   // 最初のみ残基数指定
    int coin_ = 0;      // 初期化
};