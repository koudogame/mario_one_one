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
    texture_ = LoadGraph( "Texture/mario_anime.png" );
    pos_x_ = kStartX;
    pos_y_ = kStartY;

    // ���l�̒��̃|�W�V����
    total_movement_x_ = 256;
    total_movement_y_ = 832;

    left_ = 0;
    top_ = 0;
    right_ = 0;
    bottom_ = 0;

    status_ = kMario;

    scroll_cnt_ = 0;               // �E�ɔ����������₵�Ă���

    animation_ = 0;                // �����Ă��邾���̏��
    direction_ = true;             // �����͉E����

    animation_cnt_ = 0;            // �������Ă��Ȃ��Ƃ��͓����Ȃ�
    animation_flag_ = true;        // �W�����v���Ă���Ƃ��ȊO�͈ړ����A�j���[�V����

    old_right_button_ = true;
    old_left_button_ = true;

    right_button_ = true;
    left_button_ = true;

    acceleration_ = 0;
    jumping_ = true;

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
        side_.right_shoulder_y = total_movement_y_;

        // status_��kMario�̎�
        if( status_ == kMario )
         side_.right_hand_y = total_movement_y_ + kSize;
        else
         side_.right_hand_y = total_movement_y_ + (kSize * 2);


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

        if( status_ == kMario )
            side_.left_hand_y = total_movement_y_ + kSize;
        else
            side_.left_hand_y = total_movement_y_ + (kSize * 2);


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
        total_movement_y_ = pos_y_;
    }

    ////////////////////////////////////////////////////
    // �f�o�b�O�p �������肪����܂�kEndLine��ݒ肷��
    if( status_ == kMario )
    {
        if( pos_y_ > kEndLine )
        {
            pos_y_ = kStartY - 1;
            total_movement_y_ = 831;

            // ���n        
            if( animation_flag_ == false )
            {
                animation_ = 0;
                animation_flag_ = true;
            }
            jumping_ = true;
        }
    }
    else
    {
        if( pos_y_ > kEndLine - 64)
        {
            pos_y_ = kStartY - 65;
            total_movement_y_ = 763;

            // ���n        
            if( animation_flag_ == false )
            {
                animation_ = 0;
                animation_flag_ = true;
            }
            jumping_ = true;
        }
    }
    ////////////////////////////////////////////////////

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

    if( direction_ == true )
    {
        // �E�����}���I�̕`��
        DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_,
            texture_, TRUE, FALSE );
    }
    else
    {
        // �������}���I�̕`��
        DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_,
            texture_, TRUE, TRUE );
    }
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
