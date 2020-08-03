#include "goal_fire.hpp"

void GoalFire::initialize()
{
    texture_ = LoadGraph( "Texture/mario_item.png" );

    number_ = 0;
}

void GoalFire::draw()
{
}

void GoalFire::finalize()
{
    DeleteGraph( texture_ );
}

int GoalFire::numCheck( int Number )
{
    // 花火が上がる数値なら代入
    switch( Number )
    {
    case 1:
        number_ = Number;
        break;

    case 3:
        number_ = Number;
        break;

    case 6:
        number_ = Number;
        break;

    default:
        number_ = 0;
        break;
    }

    // 花火を上げる回数を返す
    return number_;
}