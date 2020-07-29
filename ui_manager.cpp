#include "share.hpp"
#include "ui_manager.hpp"

void UIManager::initialize()
{
    // �摜�ǂݍ���
    texture_ = LoadGraph( "texture/number.png" );  


    map_.initialize();
    coin_.initialize();
}

void UIManager::update()
{
    map_.update();
    coin_.update();
}

void UIManager::draw()
{
    map_.draw( texture_ );
    coin_.draw( texture_ );
}

void UIManager::finalize()
{
    // �摜�j��
    DeleteGraph( texture_ );

    map_.finalize();
    coin_.finalize();
}

void UIManager::coinCheck( int Coin )
{
    coin_.coinCounter( Coin );
}