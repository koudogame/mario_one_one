#include "goal_fire.hpp"

void GoalFire::initialize()
{
    texture_ = LoadGraph( "Texture/mario_item.png" );

    // �ł��グ�ԉ΍��W
    position_[ 5 ].x = kFireAX;
    position_[ 5 ].y = kFireAY;
    position_[ 4 ].x = kFireBX;
    position_[ 4 ].y = kFireBY;
    position_[ 3 ].x = kFireCX;
    position_[ 3 ].y = kFireCY;
    position_[ 2 ].x = position_[ 5 ].x;
    position_[ 2 ].y = position_[ 5 ].y;
    position_[ 1 ].x = position_[ 4 ].x;
    position_[ 1 ].y = position_[ 4 ].y;
    position_[ 0 ].x = position_[ 3 ].x;
    position_[ 0 ].y = position_[ 3 ].y;

    rect_.left = 0;
    rect_.right = kSize;
    rect_.top = kSeptuple;
    rect_.bottom = kSize;

    ignition_ = true;
    scene_flag_ = true;
    number_ = 0;
    animation_cnt_ = 0;
}

void GoalFire::draw()
{
    // number_��0��葽����
    if( !ignition_ && number_ > 0 )
    DrawRectGraph( position_[ number_ - 1 ].x, position_[ number_ - 1 ].y,
        rect_.left, rect_.top, rect_.right, rect_.bottom,
        texture_, TRUE, FALSE );
}

void GoalFire::finalize()
{
    DeleteGraph( texture_ );
}

bool GoalFire::numCheck( int Number )
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
        return true;
        break;
    }

    // �ԉ΂��グ�邩�グ�Ȃ���
    return false;
}

void GoalFire::createFire()
{
    // ����
    ignition_ = false;

    // �傫���ω��p
    animation_cnt_++;

    // �A�j���[�V�����@
    if( animation_cnt_ <= 8 )
        rect_.left = 0;
    
    // �A�j���[�V�����A
    else if( animation_cnt_ <= 32 )
        rect_.left = kSize;
    
    // �I������玟�̉ԉ�
    else if( animation_cnt_ > 32 )
    {
        number_--;
        animation_cnt_ = 0;
    }

    if( number_ == 0 )
        scene_flag_ = false;
}
