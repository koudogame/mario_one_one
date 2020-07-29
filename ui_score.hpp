#pragma once 
#include "ui_base.hpp"

class UIScore :
    public UIBase
{
public :
    const int kDigitArray = 6;
    const int kStartPos = 132;

    void initialize() override;
    void update() override;
    void draw(int) override;

private :
    int score_;
};