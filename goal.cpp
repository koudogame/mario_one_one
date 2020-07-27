#include "goal.hpp"

void Goal::update( int ScreenOver )
{
    // ƒS[ƒ‹‚µ‚½‚Æ‚«‚É‰º‚Ü‚Å‰º‚°‚é
    if( !goal_flag_ )
    {
        down_cnt_++;
        if( down_cnt_ <= kDownCnt )
            item_.y += kDownSpeed;
    }
}

void Goal::draw( int Texture, const int ScreenOver)
{
    int texture_position_x = item_.x - ScreenOver;
    int texture_position_y = item_.y;

    // RECTw’è‚µ‚Ä•`‰æ‚ğs‚¤ŠÖ”
    DrawRectGraph(
        texture_position_x - kHalfSize, texture_position_y + kHalfSize,
        (int&)item_.rect.left, (int&)item_.rect.top,                   
        (int&)item_.rect.right, (int&)item_.rect.bottom,               
        Texture, TRUE, FALSE );                                        
}

void Goal::getGoal( bool Goal )
{
    goal_flag_ = Goal;
}