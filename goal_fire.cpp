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
    // �ԉ΂��オ�鐔�l�Ȃ���
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

    // �ԉ΂��グ��񐔂�Ԃ�
    return number_;
}