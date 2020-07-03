#pragma once
#include "item_base.hpp"

class Goal :
    public ItemBase
{
public : 
    static const int kDownSpeed = 6;
    static const int kDownCnt   = 66;

    Goal( Field* field ) : ItemBase( field ) {};
    void update( int ) override;
    void draw( int, const int ) override;
    void getGoal( bool ) override;

private : 
    int down_cnt_ = 0;
    bool goal_flag_ = true;
};