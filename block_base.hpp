#pragma once

// パーツ構造体
struct Parts
{
    int Id;                     // ID番号の取得
    RECT rect;                  // 切り取り範囲
    int x, y;                   // ポジション

    // 初期化
    Parts()
    {
        Id = 0;
        rect = { 0L };
        x = 0, y = 0;
    }
};

class BlockBase
{
protected:
    //Parts構造体を呼び出す
    Parts parts_;
    int base_pos_;
    bool upblock_flag_;          // true : 叩かれてない, false : 叩かれた
    bool stand_by_;              // true : 準備中, false : 動き出す

public :
    virtual void initialize(const int Id, const RECT Rect, const int X, const int Y);
    virtual void update(int);
    virtual void draw( int Texture, const int ScreenOver );
    
    virtual void downBlock();          // 体が小さいときにブロックを上げ下げする関数
    virtual void standby(int,int);     // 叩かれたときにfalseへ変える関数

    inline const int getId() {return parts_.Id; }
    inline const int getPositionX() { return parts_.x; }
    inline const int getPositionY() { return parts_.y; }
    inline void setPosition(const int& X, const int& Y) { parts_.x = X, parts_.y = Y; }
};