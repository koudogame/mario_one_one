#pragma once
#include <windows.h>
#include <DxLib.h>

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
    static const int kUsedBlock = 16;
    static const int kBrick     = 19;
    static const int kMystery   = 48;
    static const int kSize      = 64;

    virtual void initialize(const int Id, const RECT Rect, const int X, const int Y);
    virtual void update(int);
    virtual void draw( int Texture, const int ScreenOver );
    
    virtual void downBlock();
    virtual void standby(int,int);     

    inline const int getId() {return parts_.Id; }
    inline const int getPositionX() { return parts_.x; }
    inline const int getPositionY() { return parts_.y; }
    inline void setPosition(const int& X, const int& Y) { parts_.x = X, parts_.y = Y; }
};