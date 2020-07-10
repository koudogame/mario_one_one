#pragma once 
#include "data_keeper.hpp"

class BaseScene
{
public:
    // 絶対に忘れちゃいけないやつ
    virtual bool initialize() = 0;
    virtual void finalize() = 0;

    // 型名合わせて使う ( 違うと呼ばれない。)
    virtual void update() {};
    virtual void draw() {};
};