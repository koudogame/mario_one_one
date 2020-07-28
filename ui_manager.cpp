#include "share.hpp"
#include "ui_manager.hpp"

void UIManager::initialize()
{
    // ‰æ‘œ“Ç‚İ‚İ
    texture_ = LoadGraph( "texture/number.png" );  


    map_.initialize();
}

void UIManager::update()
{
    map_.update();
}

void UIManager::draw()
{
    map_.draw( texture_ );
}

void UIManager::finalize()
{
    // ‰æ‘œ”jŠü
    DeleteGraph( texture_ ); 


    map_.finalize();
}
