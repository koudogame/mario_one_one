#include "share.hpp"
#include "ui_manager.hpp"

void UIManager::initialize()
{
    // ‰æ‘œ“Ç‚İ‚İ
    texture_ = LoadGraph( "texture/number.png" );  


    map_.initialize();
    coin_.initialize();
    time_.initialize();
}

void UIManager::update( bool GoalFlag )
{    
    time_.setGoalFlag( GoalFlag );

    map_.update();
    coin_.update();
    time_.update();
}

void UIManager::draw()
{
    map_.draw( texture_ );
    coin_.draw( texture_ );
    time_.draw( texture_ );
}

void UIManager::finalize()
{
    // ‰æ‘œ”jŠü
    DeleteGraph( texture_ );

    map_.finalize();
    coin_.finalize();
    time_.finalize();
}

void UIManager::coinCheck( int Coin )
{
    coin_.coinCounter( Coin );
}