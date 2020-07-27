#include "kuribo.hpp"

void Kuribo::update( int ScreenOver )
{
    // �����o����15�}�X���O����
    if( ScreenOver > (enemy_parts_.x - (kSize * kMoveStart)) )
    {
        // �����Â���͉̂�ʓ��ɂ���Ƃ�
        if( ScreenOver <= enemy_parts_.x + kSize )
        {
            // �Ă���Ă��Ȃ���
            if( burn_ )
            {
                // ���܂�Ă��Ȃ���
                if( alive_ )
                {
                    animation();                                // �����A�j���[�V����
                    enemy_parts_.x += kSpeed * direction_;      // ��ɐi��


                    // ���̓o�^
                    body_[ kRight ][ kFoot ][ kX ] = (enemy_parts_.x + (kSize - kDisplace));
                    body_[ kRight ][ kFoot ][ kY ] = (enemy_parts_.y + kSize + 1) + kQuadruple;

                    body_[ kLeft ][ kFoot ][ kX ] = (enemy_parts_.x + kDisplace);
                    body_[ kLeft ][ kFoot ][ kY ] = (enemy_parts_.y + kSize + 1) + kQuadruple;

                    // ���ꂪ����Ƃ�
                    if( Collision::footColl() == 1 )
                    {
                        jumping_ = kNoMove;

                        int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;

                        // ���������܂��Ă��Ȃ���
                        if( block_line >= kGroundArray )
                            enemy_parts_.y = kGround;
                        else
                        enemy_parts_.y = ((block_line - kControl) * kSize) - kSize;


                        acceleration_ = 0;  // �������x
                    }
                    // ���ɕ����Ă���Ƃ�
                    else if( Collision::footColl() == 2 )
                    {
                        jumping_ = kNoJump;

                        // ���ɗ��������Ƃ�
                        if( enemy_parts_.y > kFallOut )
                        {
                            // �A�C�e������������������
                            jumping_ = kNoMove;

                            enemy_parts_.Id = kNoBlock;
                            RECT rect;
                            rect.top = enemy_parts_.Id / kLength * kSize;
                            rect.left = enemy_parts_.Id % kLength * kSize;
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
                    body_[ kRight ][ kShoulder ][ kY ] = (enemy_parts_.y + kGather) + kQuadruple;
                    body_[ kRight ][ kHands ][ kX ] = (enemy_parts_.x + kSize + 1);
                    body_[ kRight ][ kHands ][ kY ] = (enemy_parts_.y - kGather) + kQuadruple;

                    // �����蔻��̂���Ƃ�
                    if( Collision::sideColl( kRight ) == false )
                        direction_ *= -1;

                    // ����̓o�^
                    body_[ kLeft ][ kShoulder ][ kX ] = (enemy_parts_.x - 1);
                    body_[ kLeft ][ kShoulder ][ kY ] = (enemy_parts_.y + kGather) + kQuadruple;
                    body_[ kLeft ][ kHands ][ kX ] = (enemy_parts_.x - 1);
                    body_[ kLeft ][ kHands ][ kY ] = (enemy_parts_.y - kGather) + kQuadruple;

                    // �����蔻��̂���Ƃ�
                    if( Collision::sideColl( kLeft ) == false )
                        direction_ *= -1;
                }
                else
                {
                    // ���܂ꂽ��ɏ�����܂�
                    if( death_cnt_ < kDeathTime )
                    {
                        death_cnt_++;
                    }
                    else
                    {
                        enemy_parts_.Id = kNoBlock;
                        RECT rect;
                        rect.top = enemy_parts_.Id / kLength * kSize;
                        rect.left = enemy_parts_.Id % kLength * kSize;
                        rect.bottom = kSize;
                        rect.right = kSize;
                        enemy_parts_.rect = rect;
                    }
                }
            }
            // �Ă��ꂽ�Ƃ��̏���
            else
            {
                // ���߂�ꂽ�ʒu�܂ŗ���������
                if( enemy_parts_.y < kFieldSize )
                {
                    // �d�͂𔽉f�����Ȃ��痎��
                    acceleration_ += kGravity;

                    enemy_parts_.x += 2;
                    enemy_parts_.y += acceleration_;
                }
            }
        }
    }
}

int Kuribo::getPosX()
{
    if(burn_)
    return (enemy_parts_.x - 1);

    return 0;
}

int Kuribo::getPosY()
{
    if( burn_ )
        return (enemy_parts_.y - 1) + kQuadruple;
    
    return 0;
}

// �}���I�Ƃ̏Փ˂��������Ƃ�
void Kuribo::posCollision(int Touch)
{
    // �A�C�e������������������
    jumping_ = kNoMove;

    enemy_parts_.Id = kDead;
    RECT rect;
    rect.top = enemy_parts_.Id / kLength * kSize;
    rect.left = enemy_parts_.Id % kLength * kSize;
    rect.bottom = kSize;
    rect.right = kSize;
    enemy_parts_.rect = rect;
    enemy_parts_.y += kDown;

    alive_ = false;
}

// �����A�j���[�V����
void Kuribo::animation()
{
    animation_++;

    if( animation_ > kCountup )
    {
        animation_ = 0;
        walk_animation_ *= -1;
    }

    if( walk_animation_ == -1 )
    {
        enemy_parts_.rect.left = 0;
        enemy_parts_.rect.right = kSize;
    }
    else
    {
        enemy_parts_.rect.left = kSize;
        enemy_parts_.rect.right = kSize;
    }
}
