#include "brick.hpp"

void Brick::initialize( const int Id, const RECT Rect, const int X, const int Y )
{
    // �x�[�X�̏�����
    BlockBase::initialize( Id, Rect, X, Y );

    // �@����Ă��Ȃ����
    punch_ = true;
}

void Brick::update(int Status)
{
    // �@���ꂽ�Ƃ�
    if( !stand_by_ )
    {
        // ��x����̏���
        if( punch_ )
        {
            // �}���I����Ȃ��Ƃ�
            if( Status != kMario )
            {
                // �����K���@���ꂽ�Ƃ�
                parts_.Id = kNoBlock;
                RECT rect;
                rect.top = kNoBlock / 16 * kSize;
                rect.left = kNoBlock % 16 * kSize;
                rect.bottom = kSize;
                rect.right = kSize;
                parts_.rect = rect;

                // �E���A�������W��o�^����
                for( int i = 0; i < kBodyParts; i++ )
                {
                    break_parts_[ i ][ kX ] = (pos_x_ * kSize);
                    break_parts_[ i ][ kY ] = (pos_y_ * kSize);
                }

                // �W�����v�͂̐ݒ�
                acceleration_up_ = -kJumpUp;
                acceleration_down_ = -kJumpDown;

                punch_ = false;
            }
            else
            {
                base_pos_ = parts_.y;
                parts_.y -= kSize / 4;
                upblock_flag_ = false;
                stand_by_ = true;
            }
        }

        // ��������u���b�N�𗎉������鏈����g��
        if( !stand_by_ )
        {
            for( int i = 0; i < kBodyParts; i++ )
            {
                // X���W�̈ړ�
                if( (i % 2) == 0 )
                    break_parts_[ i ][ kX ] += kSpeed;
                else
                    break_parts_[ i ][ kX ] -= kSpeed;

                // Y���W�̈ړ�
                if( i < 2 )
                    break_parts_[ i ][ kY ] += acceleration_up_;
                else
                    break_parts_[ i ][ kY ] += acceleration_down_;
            }

            // �W�����v�͂�t�^
            acceleration_up_ += kGravity;
            acceleration_down_ += kGravity;
        }
    }
}

// �`�揈��
void Brick::draw( int Texture, int ScreenOver)
{
    // �x�[�X�̏������Ă�
    BlockBase::draw( Texture, ScreenOver );

    if( !stand_by_ )
    {
        for( int i = 0; i < kBodyParts; i++ )
        {
            int texture_position_x = break_parts_[ i ][ kX ] - ScreenOver;
            int texture_position_y = break_parts_[ i ][ kY ];

            DrawRectGraph(
                (texture_position_x), (texture_position_y - (kSize * 4)),
                (kSize * 3), kSize, (kSize / 2), (kSize / 2), Texture, TRUE, FALSE );
        }
    }
}

// �@���ꂽ�Ƃ����ɉ�����
void Brick::downBlock()
{
    if( !upblock_flag_ )
    {
        if( parts_.y < base_pos_ )
        {
            parts_.y += 2;
        }
        else          
            upblock_flag_ = true;
    }
}

// �@���ꂽ�� false�֕ύX
void Brick::standby(int x, int y)
{
    pos_x_ = x;
    pos_y_ = y;

    stand_by_ = false;
}
