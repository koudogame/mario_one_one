#include "turtle.hpp"

void Turtle::update( int ScreenOver )
{
    // �����o����15�}�X���O����
    if( ScreenOver > (enemy_parts_.x - (kSize * 20)) )
    {
        // �����Â���͉̂�ʓ��ɂ���Ƃ�
        if( ScreenOver <= enemy_parts_.x + kSize )
        {
            if( burn_ )
            {
                if( active_ )
                {
                    animation();
                    enemy_parts_.x += kSpeed * direction_;      // ��ɐi��
                }
                else if( !pushout_ && !active_ )
                {
                    enemy_parts_.x += kMaxSpeed * direction_;
                }

                // ���̓o�^
                body_[ kRight ][ kFoot ][ kX ] = (enemy_parts_.x + (kSize - 5));
                body_[ kRight ][ kFoot ][ kY ] = (enemy_parts_.y + kSize + 1) + (kSize * 4);

                body_[ kLeft ][ kFoot ][ kX ] = (enemy_parts_.x + 5);
                body_[ kLeft ][ kFoot ][ kY ] = (enemy_parts_.y + kSize + 1) + (kSize * 4);

                // ���ꂪ����Ƃ�
                if( Collision::footColl() == 1 )
                {
                    jumping_ = kNoMove;
                    acceleration_ = 0;  // �������x

                    int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;
                    enemy_parts_.y = ((block_line - 4) * kSize) - 1;

                    if( block_line >= 14 )
                        enemy_parts_.y = kGround;
                }
                // ���ɕ����Ă���Ƃ�
                else if( Collision::footColl() == 2 )
                {
                    jumping_ = kNoJump;

                    if( enemy_parts_.y > 670 )
                    {
                        // �A�C�e������������������
                        jumping_ = kNoMove;

                        enemy_parts_.Id = kNoBlock;
                        RECT rect;
                        rect.top = enemy_parts_.Id / 16 * kSize;
                        rect.left = enemy_parts_.Id % 16 * kSize;
                        rect.bottom = kSize;
                        rect.right = kSize;
                        enemy_parts_.rect = rect;
                    }

                    // ���ɕ����Ă���Ƃ�����
                    if( jumping_ == kNoJump )
                    {
                        acceleration_ += kGravity;
                        enemy_parts_.y += acceleration_;
                    }
                }

                // �E��̓o�^
                body_[ kRight ][ kShoulder ][ kX ] = (enemy_parts_.x + kSize + 1);
                body_[ kRight ][ kShoulder ][ kY ] = (enemy_parts_.y + 10) + (kSize * 4);
                body_[ kRight ][ kHands ][ kX ] = (enemy_parts_.x + kSize + 1);
                body_[ kRight ][ kHands ][ kY ] = (enemy_parts_.y - 10) + (kSize * 4);

                // �����蔻��̂���Ƃ�
                if( Collision::sideColl( kRight ) == false )
                    direction_ *= -1;

                // ����̓o�^
                body_[ kLeft ][ kShoulder ][ kX ] = (enemy_parts_.x - 1);
                body_[ kLeft ][ kShoulder ][ kY ] = (enemy_parts_.y + 10) + (kSize * 4);
                body_[ kLeft ][ kHands ][ kX ] = (enemy_parts_.x - 1);
                body_[ kLeft ][ kHands ][ kY ] = (enemy_parts_.y - 10) + (kSize * 4);

                // �����蔻��̂���Ƃ�
                if( Collision::sideColl( kLeft ) == false )
                    direction_ *= -1;
            }
            else
            if( enemy_parts_.y < kFieldSize )
            {
                enemy_parts_.rect.left = kSize;
                enemy_parts_.rect.top = kSize * 7;
                enemy_parts_.rect.right = kSize;
                enemy_parts_.rect.bottom = kSize;


                // �d�͂𔽉f�����Ȃ��痎��
                acceleration_ += kGravity;

                enemy_parts_.x += 2;
                enemy_parts_.y += acceleration_;
            }
        }
    }
}

int Turtle::getPosX()
{
    if(burn_)
    return (enemy_parts_.x - 1);

    return 0;
}

int Turtle::getPosY()
{
    if(burn_)
    return (enemy_parts_.y - 1) + (kSize * 4);

    return 0;
}

void Turtle::posCollision( int Touch )
{
    if( Touch == 1 )
    {
        // �N���Ă�Ƃ��ɒ@������
        if( active_ )
        {
            enemy_parts_.Id = 113;
            RECT rect;
            rect.top = kShell / 16 * kSize;
            rect.left = kShell % 16 * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            enemy_parts_.rect = rect;

            active_ = false;          // �b���̒��ɓ���
        }
    }
    else if( Touch == 2 )
    {
        pushout_    = false;
        direction_  = 1;
        action_cnt_ = 1;

        enemy_parts_.x += 6;
    }
    else if( Touch == 3 )
    {
        pushout_    = false;
        direction_  = -1;
        action_cnt_ = 1;

        enemy_parts_.x -= 6;
    }
}
void Turtle::shellCollision()
{
    ++action_cnt_;

    if( action_cnt_ == 1 )
    {
        pushout_ = false;
        direction_ = 1;
    }
    else if( action_cnt_ == 3 )
    {
        pushout_ = true;
        action_cnt_ = 0;
    }
}

void Turtle::fireCollision()
{
    EnemyBase::fireCollision();

    enemy_parts_.rect.left = kSize;
    enemy_parts_.rect.top = kSize * 7;
    enemy_parts_.rect.right = kSize;
    enemy_parts_.rect.bottom = kSize;
}

void Turtle::animation()
{
    animation_++;

    if( animation_ > 8 )
    {
        animation_ = 0;
        walk_animation_ *= -1;
    }

    if( walk_animation_ == -1 )
    {
        enemy_parts_.rect.left = kSize * 4;
        enemy_parts_.rect.right = kSize;
    }
    else
    {
        enemy_parts_.rect.left = kSize * 5;
        enemy_parts_.rect.right = kSize;
    }

    enemy_parts_.rect.top = kSize * 2;
    enemy_parts_.rect.bottom = static_cast<int>(kSize * 1.5);
}
