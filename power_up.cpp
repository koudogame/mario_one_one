#include "power_up.hpp"

void Powerup::update( int Screenover )
{
    if( !up_ )
    {
        // ��x����Status�̊m�F���s��
        if( punch_ )
        {
            // Status�m�F���A�o���A�C�e����I������
            if( status_ == kMario )
            {
                item_.Id = kMashroom;
                RECT rect;
                rect.top = item_.Id / kLength * kSize;
                rect.left = item_.Id % kLength * kSize;
                rect.bottom = kSize;
                rect.right = kSize;
                item_.rect = rect;

                up_cnt_ += 16;
                item_.y -= 16;

                punch_ = false;
            }
            else
            {
                item_.Id = kFlower;
                RECT rect;
                rect.top = item_.Id / kLength * kSize;
                rect.left = item_.Id % kLength * kSize;
                rect.bottom = kSize;
                rect.right = kSize;
                item_.rect = rect;

                up_cnt_ += 16;
                item_.y -= 16;

                punch_ = false;
            }
        }

        // �u���b�N�̏�ɏo�؂�܂�
        if( up_flag_ )
        {
            if( up_cnt_ <= kSize )
            {
                up_cnt_++;
                item_.y--;
            }
            else
                up_flag_ = false;
        }
        else
        {
            // �L�m�R�̎�
            if( item_.Id == kMashroom )
            {
                if( Screenover <= item_.x + kSize )
                    item_.x += kSpeed * direction_;      // ��ɐi��

                    // ���̓o�^
                body_[ kRight ][ kFoot ][ kX ] = (item_.x + (kSize - kGather));
                body_[ kRight ][ kFoot ][ kY ] = (item_.y + kSize + 1) + kQuadruple;

                body_[ kLeft ][ kFoot ][ kX ] = (item_.x + kGather);
                body_[ kLeft ][ kFoot ][ kY ] = (item_.y + kSize + 1) + kQuadruple;

                // ���ꂪ����Ƃ�
                if( Collision::footColl() == 1 )
                {
                    jumping_ = kNoMove;
                    acceleration_ = 0;  // �������x

                    int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;

                    if( block_line >= kGroundArray )
                        item_.y = kGround;
                    else
                        item_.y = ((block_line - kControl) * kSize) - 1;

                }
                // ���ɕ����Ă���Ƃ�
                else if( Collision::footColl() == 2 )
                {
                    jumping_ = kNoJump;

                    if( item_.y > kFallOut )
                    {
                        // �A�C�e������������������
                        jumping_ = kNoMove;

                        item_.Id = kNoBlock;
                        RECT rect;
                        rect.top = item_.Id / kLength * kSize;
                        rect.left = item_.Id % kLength * kSize;
                        rect.bottom = kSize;
                        rect.right = kSize;
                        item_.rect = rect;
                    }

                    // ���ɕ����Ă���Ƃ�����
                    if( jumping_ == kNoJump )
                    {
                        acceleration_ += kGravity;
                        item_.y += acceleration_;
                    }
                }

                // �E��̓o�^
                body_[ kRight ][ kShoulder ][ kX ] = (item_.x + kSize + 1);
                body_[ kRight ][ kShoulder ][ kY ] = (item_.y + kGather) + kQuadruple;
                body_[ kRight ][ kHands ][ kX ] = (item_.x + kSize + 1);
                body_[ kRight ][ kHands ][ kY ] = (item_.y - kGather) + kQuadruple;

                if( turn_ )
                    // �����蔻��̂���Ƃ�
                    if( Collision::sideColl( kRight ) == false )
                    {
                        turn_ = false;
                        direction_ *= -1;
                    }

                // ����̓o�^
                body_[ kLeft ][ kShoulder ][ kX ] = (item_.x - 1);
                body_[ kLeft ][ kShoulder ][ kY ] = (item_.y + kGather) + kQuadruple;
                body_[ kLeft ][ kHands ][ kX ] = (item_.x - 1);
                body_[ kLeft ][ kHands ][ kY ] = (item_.y - kGather) + kQuadruple;

                if( turn_ )
                    // �����蔻��̂���Ƃ�
                    if( Collision::sideColl( kLeft ) == false )
                    {
                        turn_ = false;
                        direction_ *= -1;
                    }
            }
            else if( item_.Id == kFlower )
                // �t�����[�����炫�炳����
                flowerAnimation();
        }
    }
}

// ��x�����Ă΂Ȃ��悤�ɂ��邽��
void Powerup::flagChange( int Status )
{
    up_ = false;
    jumping_ = kJump;
    status_ = Status;
}

int Powerup::getPosX()
{
    if( !up_flag_ )
    return (item_.x - 1);

    return 0;
}

int Powerup::getPosY()
{
    if( !up_flag_ )
    return (item_.y - 1) + kQuadruple;

    return 0;
}

// �}���I�Ɠ��������Ƃ�
void Powerup::posCollision()
{
    // �A�C�e������������������
    jumping_ = kNoMove;

    item_.y = kFallOut;

    item_.Id = kNoBlock;
    RECT rect;
    rect.top = item_.Id / kLength * kSize;
    rect.left = item_.Id % kLength * kSize;
    rect.bottom = kSize;
    rect.right = kSize;
    item_.rect = rect;
}

// �t�����[�̂��炫��A�j���[�V����
void Powerup::flowerAnimation()
{
    animation_cnt_++;

    if( animation_cnt_ > 2 )
    {
        animation_cnt_ = 0;
        flower_animation_ += 1;

        if( flower_animation_ >= 3 )
            flower_animation_ = 0;
    }

    item_.rect.left = flower_animation_ * kSize;
    item_.rect.right = kSize;
}
