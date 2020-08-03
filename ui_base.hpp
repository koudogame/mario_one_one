#pragma once

class UIBase
{
public:
    virtual void initialize() {};
    virtual void update() {};
    virtual void draw( int ) {};
    virtual void finalize() {};

protected:
    const int kUIposY = 50;     // UI�����
    const int kTimeScore = 50;  // �X�R�A

    // Rect���g�p
    Rect<int> rect_{ 0, kQuarterSize, 0, kQuarterSize };
    int digit_[ 6 ] = { 0 };    // �ő�U���܂�
};