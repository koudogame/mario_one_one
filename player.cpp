#include "player.hpp"

Player::Player( Field* field )
{
    field_ = field;
    texture_ = NULL;
    
    // �ڂɌ�����|�W�V����
    pos_x_ = kStartX;
    pos_y_ = kStartY;

    // ���l�̒��̃|�W�V����
    total_movement_x_ = 256;
    total_movement_y_ = 832;
}

Player::~Player()
{
}

bool Player::initialize()
{
    texture_          = LoadGraph( "Texture/mario_anime.png" );
    pos_x_            = kStartX;
    pos_y_            = kStartY;

    // ���l�̒��̃|�W�V����
    total_movement_x_ = 256;
    total_movement_y_ = 832;

    left_             = 0;
    top_              = 0;
    right_            = 0;
    bottom_           = 0;

    status_           = kMario;

    scroll_cnt_       = 0;            // �E�ɔ����������₵�Ă���

    animation_        = 0;            // �����Ă��邾���̏��
    direction_        = true;         // �����͉E����

    animation_cnt_    = 0;            // �������Ă��Ȃ��Ƃ��͓����Ȃ�
    animation_flag_   = true;         // �W�����v���Ă���Ƃ��ȊO�͈ړ����A�j���[�V����

    old_right_button_ = true;
    old_left_button_  = true;

    right_button_     = true;
    left_button_      = true;

    acceleration_     = 0;
    jumping_          = true;

    break_right_x_    = 0;
    break_right_y_    = 0;

    break_left_x_     = 0;
    break_left_y_     = 0;

    // �n�܂����Ƃ�status_��kMario�ȊO�Ȃ�
    if( status_ != kMario )
    {
        pos_y_ -= kSize;
        total_movement_y_ -= kSize;
    }

    return true;
}

void Player::update()
{
    // �E����
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_RIGHT) == 0 )
    {
        direction_ = true;         // �������E�����ɕς���
        right_button_ = false;     // �����Ă���(�g���b�J�[)            
        
        // ��Ɨ��T�C�h�͕ύX�Ȃ�
        side_.right_shoulder_x = total_movement_x_ + kSize + 1;
        side_.right_hand_x = total_movement_x_ + kSize + 1;
        side_.right_shoulder_y = total_movement_y_ + 1;

        // status_��kMario�̎�
        if( status_ == kMario )
         side_.right_hand_y = total_movement_y_ + kSize - 1;
        else
         side_.right_hand_y = total_movement_y_ + (kSize * 2) - 1;


        // �����蔻��̂Ȃ��u���b�N�̂Ƃ�
        if( field_->getRightShoulderId( side_ ) > 64 &&
            field_->getRightHandId( side_ ) > 64 )
        {

            // �E�ւ̈ړ�
            pos_x_ += kSpeed;
            total_movement_x_ += kSpeed;

            // pos_x_ �Z���^�[�𒴂���Ƃ�
            if( pos_x_ > kEndLine )
            {
                scroll_cnt_ += kSpeed;
                pos_x_ = kEndLine;
            }
        }

        // �f�o�b�O�p�ϐ�
        int shoulder = field_->getRightShoulderId( side_ );
        int hand = field_->getRightHandId( side_ );

        animation();               // �����Ă���A�j���[�V����
    }
    else
        right_button_ = true;

    // ������
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_LEFT) == 0 )
    {
        direction_ = false;        // �������������ɕς���
        left_button_ = false;      // �����Ă���

        // ��Ɨ��T�C�h�͕ύX�Ȃ�
        side_.left_shoulder_x = total_movement_x_ - 1;
        side_.left_hand_x     = total_movement_x_ - 1;
        side_.left_shoulder_y = total_movement_y_;

        // ���̈ʒu������Ԃɉ����ĕύX����
        if( status_ == kMario )
            side_.left_hand_y = total_movement_y_ + kSize - 1;
        else
            side_.left_hand_y = total_movement_y_ + (kSize * 2) - 1;


        // �}���I�̉E���ɏՓ˂���u���b�N���Ȃ��Ƃ�
        if( field_->getLeftShoulderId( side_ ) > 64 &&
            field_->getLeftHandId( side_ ) > 64 )
        {
            // �|�W�V�����[����荶�̎�
            if( pos_x_ <= 0 )
            {
                pos_x_ = 0;
            }
            // ���ǈȊO�̎�
            else
            {
                pos_x_ -= kSpeed;
                total_movement_x_ -= kSpeed;
            }
        }

        animation();               // �����Ă���A�j���[�V����
    }
    else
        left_button_ = true;

    // ���͂��I������Ƃ��ɔ�r����
    if( old_left_button_ == false && left_button_ == true ||
        old_right_button_ == false && right_button_ == true )
    {
        animation_ = 0;
        animation_cnt_ = 0;
    }        
    
    // �ߋ��Ɉ����p��
    old_left_button_ = left_button_;
    old_right_button_ = right_button_;

    // �W�����v����
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_B) == 0 )
    {
        // �W�����vRECT�ɐ؂�ւ�
        // kMario��Ԃ̎��̂ݗL��
        animation_ = 4;
        
        // �W�����v���ɃA�j���[�V�����𓮂����Ȃ��悤�ɂ���
        animation_flag_ = false;

        // ���n������Ăє�ׂ�悤�ɂ���
        if( jumping_ == true )
        {
            jumping_ = false;
            acceleration_ = -kJumpPower;
        }
    }

    // �W�����v���������d�͂�������
    if( jumping_ == false )
    {
        acceleration_ += kGravity;

        // �}���I���΂�
        pos_y_ += acceleration_;
        total_movement_y_ += acceleration_;
    }

    // �Q�i���n���Ȃ��悤�ɂ��閂�@�̐���
    if( acceleration_ >= 20)
    {
        acceleration_ = 20;
    }

    // �}���I�̓�
    updown_.right_head_x     = total_movement_x_ + kSize;
    updown_.right_head_y     = total_movement_y_ - 1;
    updown_.left_head_x      = total_movement_x_;
    updown_.left_head_y      = total_movement_y_ - 1;

    // �}���I�̑���
    updown_.right_foot_x     = total_movement_x_ + kSize;
    updown_.left_foot_x      = total_movement_x_;

    if( status_ == kMario )
    {
        updown_.right_foot_y = total_movement_y_ + kSize + 1;
        updown_.left_foot_y  = total_movement_y_ + kSize + 1;
    }
    else
    {
        updown_.right_foot_y = total_movement_y_ + (kSize * 2) + 1;
        updown_.left_foot_y  = total_movement_y_ + (kSize * 2) + 1;
    }

    // ��֔��ł���Ƃ��ɂ���hit()���Ă�
    if( acceleration_ < 0 )
    {
        // ���̏�ɂ��鎞
        if( field_->getRightHeadId( updown_ ) <= 64
            || field_->getLeftHeadId( updown_ ) <= 64 )
        {
            // �E���ɂ�����Ƃ�
            if( field_->getRightHeadId( updown_ ) <= 64 )
            {
                break_right_x_ = (total_movement_x_ / 64) + 1;
                break_right_y_ = total_movement_y_ / 64;
            }

            // �����ɂ�����Ƃ�
            if( field_->getLeftHeadId( updown_ ) <= 64 )
            {
                break_left_x_ = total_movement_x_ / 64;
                break_left_y_ = total_movement_y_ / 64;
            }
            // �f�o�b�O�p�ϐ�
            int Head = field_->getRightHeadId( updown_ );
            int Foot = field_->getRightFootId( updown_ );

            // �����Ԃ����Ƃ��̔���
            hit();
        }
    }
    // ��֔�ԉ������Ȃ��Ȃ����Ƃ��ɉ��̔�������n�߂�
    else
    {
        // �����̏Փ˔���
        collision();
    }
}

void Player::draw()
{
    // ��Ԃ͕ς���Ă�width�͕ς��Ȃ�
    left_ = animation_ * kSize;
    right_ = kSize;

    // �}���I�̂Ƃ�
    if( status_ == kMario )
    {
        top_ = kMario * kSize;
        bottom_ = top_ + kSize;
    }
    // �X�[�p�[�}���I�̂Ƃ�
    else if( status_ == kSuperMario )
    {
        top_ = kSize * 4;
        bottom_ = kSize * 2;
    }
    // �t�@�C�A�}���I�̂Ƃ�
    else if( status_ == kFireMario )
    {
        top_ = kSize * 8;
        bottom_ = kSize * 2;
    }
    // �E�����}���I�̕`��
    DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_,
        texture_, TRUE, !direction_ );
}

void Player::finalize()
{
    // �e�N�X�`���J��
    DeleteGraph( texture_ );
}

void Player::animation()
{
    // �����Ă��ǂ������ׂ�
    if( animation_flag_ == true )
    {
        animation_cnt_++;

        if( animation_cnt_ >= 5 )
        {
            animation_cnt_ = 0;

            if( animation_ <= 2 )
            {
                animation_++;
            }
            else
            {
                animation_ = 1;
            }
        }
    }

}

void Player::collision()
{
    // �����ɂ���u���b�N������Ƃ�
    if( field_->getRightFootId( updown_ ) <= 64 ||
        field_->getLeftFootId( updown_ ) <= 64 )
    {
        landing();          // ���n����

        acceleration_ = 0;  // �������x

        int block_line = std::round( static_cast<float>(total_movement_y_) / 64 );
        pos_y_ = (block_line - 4) * 64;
        total_movement_y_ = block_line * 64;
    }
    // �����ɉ����Ȃ������Ă���Ƃ�
    else if( field_->getRightFootId( updown_ ) == kSkyBlue && field_->getLeftFootId( updown_ ) == kSkyBlue )
    {
        // ��ׂȂ��悤�ɂ���
        jumping_ = false;

        // �}���I����ʊO���ɍs�����Ƃ�
        if( pos_y_ > 670 )
        {
            // gameover
            acceleration_ = -kJumpPower;
        }
    }
    // �����ɂ���u���b�N�����Ȃ��Ƃ�
    else
    {
        if( status_ == kMario )
        {
            // ����艺�̎�
            if( pos_y_ > kEndLine )
            {
                landing(); // ���n����

                pos_y_ = kStartY - 1;
                total_movement_y_ = 831;
            }
        }
        else
        {
            // ����艺�̎�
            if( pos_y_ > kEndLine - 64 )
            {
                landing(); // ���n����

                pos_y_ = kStartY - 65;
                total_movement_y_ = 763;
            }
        }
    }
}

void Player::landing()
{
    // �t���O���Z�b�g        
    if( animation_flag_ == false )
    {
        animation_ = 0;
        animation_flag_ = true;
    }
    jumping_ = true;
}

void Player::hit()
{
    // ��ւ̉����x�𖳂���
    acceleration_ = 0;

    int block_line = std::round( static_cast<float>(total_movement_y_) / 64 );

    // �v���C���[�̗��ꏊ����̕ӂ̍����ɂ���
    pos_y_ = (block_line - 4) * 64;
    total_movement_y_ = block_line * 64;
}

