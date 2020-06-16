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

    animation_ = 0;            // �����Ă��邾���̏��
    direction_ = true;          // �����͉E����

    return true;
}

void Player::update()
{
}

void Player::draw()
{
    // �}���I�̂Ƃ�
    if( status_ == kMario )
    {
        left_ = animation_ * kSize;
        top_ = kMario;

        right_ = left_ + kSize;
        bottom_ = top_ + kSize;
    }
    // else if( status_ == kSuperMario){}��ǉ�����

    // �}���I���E�������Ă���Ƃ�
    if( direction_ == true )
    {
        // �}���I�̕`��
        DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_,
            texture_, TRUE, FALSE );
    }
}

void Player::finalize()
{
    // �e�N�X�`���J��
    DeleteGraph( texture_ );
}
