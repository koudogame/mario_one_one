#include "fireboll.hpp"

void FireBoll::initialize()
{
    texture_ = LoadGraph( "Texture/mario_field.png" );
}

void FireBoll::update( int PosX, int PosY, int Status, int Direction)
{
}

void FireBoll::draw()
{
    //DrawRectGraph()
}

void FireBoll::finalize()
{
    DeleteGraph( texture_ );
}
