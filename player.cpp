#include "player.hpp"

Player::Player()
{
    texture_ = NULL;
    pos_x_ = kStartX;
    pos_y_ = kStartY;
}

Player::~Player()
{
}

bool Player::initialize()
{
    texture_ = LoadGraph( "Texture/mario_anime.png" );
    pos_x_ = kStartX;
    pos_y_ = kStartY;

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

    return true;
}

void Player::update()
{
    // �E����
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_RIGHT) == 0 )
    {
        direction_ = true;         // �������E�����ɕς���
        right_button_ = false;     // �����Ă��� 


        animation();               // �����Ă���A�j���[�V����


        pos_x_ += kSpeed;          // �E�ւ̈ړ�


                                   // pos_x_ �Z���^�[�𒴂���Ƃ�
        if( pos_x_ > kEndLine )
        {
            scroll_cnt_ += kSpeed;
            pos_x_ = kEndLine;
        }
    }
    else
        right_button_ = true;

    // ������
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_LEFT) == 0 )
    {
        direction_ = false;        // �������������ɕς���
        left_button_ = false;      // �����Ă���


        animation();               // �����Ă���A�j���[�V����


        // �|�W�V�����[����荶�̎�
        if( pos_x_ <= 0 )
        {
            pos_x_ = 0;
        }
        // ���ǈȊO�̎�
        else
        {
            pos_x_ -= kSpeed;
        }
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
    }
}

void Player::draw()
{
    // �}���I�̂Ƃ�
    if( status_ == kMario )
    {
        left_ = animation_ * kSize;
        top_ = kMario;

        right_ = kSize;
        bottom_ = top_ + kSize;
    }
    // else if( status_ == kSuperMario){}��ǉ�����

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
