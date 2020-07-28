#pragma once

class UIBase
{
public:
    virtual void initialize() {};
    virtual void update() {};
    virtual void draw( int ) {};
    virtual void finalize() {};

protected:
    Rect<int> rect_;           // Rectを使用

    const int kUIposY = 50;    // UI高さ基準
    int number_a_;             // Aの数値
    int number_b_;             // Bの数値
};
