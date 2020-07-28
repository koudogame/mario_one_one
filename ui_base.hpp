#pragma once

class UIBase
{
public:
    virtual void initialize() {};
    virtual void update() {};
    virtual void draw( int ) {};
    virtual void finalize() {};

protected:
    Rect<int> rect_;           // Rect���g�p

    const int kUIposY = 50;    // UI�����
    int number_a_;             // A�̐��l
    int number_b_;             // B�̐��l
};
