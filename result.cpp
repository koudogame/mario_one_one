#include "result.hpp"

bool ResultScene::initialize()
{
    texture_ = LoadGraph( "Texture/ayaka.jpg" );

    return false;
}

void ResultScene::update()
{
}

void ResultScene::draw()
{
    SetTransColor( 255, 255, 255 );
    DrawGraph( 0, 0, texture_, TRUE );
}

void ResultScene::finalize()
{
    DeleteGraph( texture_ );
}