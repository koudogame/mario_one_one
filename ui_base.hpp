#pragma once

class UIBase
{
public:
    virtual void initialize() {};
    virtual void update() {};
    virtual void draw( int ) {};
    virtual void finalize() {};

protected:
    const int kUIposY = 50;     // UI高さ基準
    const int kTimeScore = 50;  // スコア

    // Rectを使用
    Rect<int> rect_{ 0, kQuarterSize, 0, kQuarterSize };
    int digit_[ 6 ] = { 0 };    // 最大６桁まで
};