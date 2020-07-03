#include "player.hpp"

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

    status_           = kFireMario;
    past_status_      = status_;

    scroll_cnt_       = 0;            // �E�ɔ����������₵�Ă���

    gameover_flag_    = true;         // ���ꂪ�������玀��

    animation_        = 0;            // �����Ă��邾���̏��
    direction_        = true;         // �����͉E����

    animation_cnt_    = 0;            // �������Ă��Ȃ��Ƃ��͓����Ȃ�
    animation_flag_   = true;         // �W�����v���Ă���Ƃ��ȊO�͈ړ����A�j���[�V����

    old_right_button_ = true;
    old_left_button_  = true;

    right_button_     = true;
    left_button_      = true;

    acceleration_     = 0;
    jumping_          = kJump;

    break_right_x_    = 0;
    break_right_y_    = 0;

    break_left_x_     = 0;
    break_left_y_     = 0;

    invincible_       = true;
    invincible_cnt_   = 0;

    goal_flag_        = true;
    catch_flag_       = true;
    extinguish_existence_ = true;

    // �n�܂����Ƃ�status_��kMario�ȊO�Ȃ�
    if( status_ != kMario )
    {
        pos_y_ -= kSize;
        total_movement_y_ -= kSize;
    }

    return true;
}

bool Player::update()
{
    if( !goal_flag_ ) Ending();
        
    // GameOver����
    else if( gameover_flag_ )
    {
        // �E����
        if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_RIGHT) == 0 )
        {
            direction_ = true;         // �������E�����ɕς���
            right_button_ = false;     // �����Ă���(�g���b�J�[)    

            body_[ kRight ][ kShoulder ][ kX ] = (total_movement_x_ + kSize + 1);
            body_[ kRight ][ kShoulder ][ kY ] = (total_movement_y_);

            body_[ kRight ][ kHands ][ kX ] = (total_movement_x_ + kSize + 1);
            // status_��kMario�̎�
            if( status_ == kMario )
                body_[ kRight ][ kHands ][ kY ] = (total_movement_y_ + kSize - 1);
            else
                body_[ kRight ][ kHands ][ kY ] = (total_movement_y_ + (kSize * 2) - 1);

            // �����蔻��̂Ȃ��u���b�N�̂Ƃ�
            if( Collision::sideColl( kRight ) == true )
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
            body_[ kLeft ][ kShoulder ][ kX ] = (total_movement_x_ - 1);
            body_[ kLeft ][ kShoulder ][ kY ] = (total_movement_y_);

            body_[ kLeft ][ kHands ][ kX ] = (total_movement_x_ - 1);

            // ���̈ʒu������Ԃɉ����ĕύX����
            if( status_ == kMario )
                body_[ kLeft ][ kHands ][ kY ] = (total_movement_y_ + kSize - 1);
            else
                body_[ kLeft ][ kHands ][ kY ] = (total_movement_y_ + (kSize * 2) - 1);

            // �}���I�̍����ɏՓ˂���u���b�N���Ȃ��Ƃ�
            if( Collision::sideColl( kLeft ) == true )
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

            if( jumping_ == kJump )
            {
                jumping_ = kNoJump;
                acceleration_ = -kJumpPower;
            }
        }

        // �W�����v���������d�͂�������
        if( jumping_ == kNoJump )
        {
            acceleration_ += kGravity;

            // �}���I���΂�
            pos_y_ += acceleration_;
            total_movement_y_ += acceleration_;
        }

        // �Q�i���n���Ȃ��悤�ɂ��閂�@�̐���
        if( acceleration_ >= 20 )
        {
            acceleration_ = 20;
        }

        // �}���I�̓�(�������E10������)
        body_[ kRight ][ kHead ][ kX ] = (total_movement_x_ + (kSize - 10));
        body_[ kRight ][ kHead ][ kY ] = (total_movement_y_ - 1);
        body_[ kLeft ][ kHead ][ kX ] = (total_movement_x_ + 10);
        body_[ kLeft ][ kHead ][ kY ] = (total_movement_y_ - 1);

        // �}���I�̑���
        body_[ kRight ][ kFoot ][ kX ] = (total_movement_x_ + (kSize - 10));
        body_[ kLeft ][ kFoot ][ kX ] = (total_movement_x_ + 10);

        if( status_ == kMario )
        {
            body_[ kRight ][ kFoot ][ kY ] = (total_movement_y_ + kSize + 1);
            body_[ kLeft ][ kFoot ][ kY ] = (total_movement_y_ + kSize + 1);
        }
        else
        {
            body_[ kRight ][ kFoot ][ kY ] = (total_movement_y_ + (kSize * 2) + 1);
            body_[ kLeft ][ kFoot ][ kY ] = (total_movement_y_ + (kSize * 2) + 1);
        }

        // ��֔��ł���Ƃ��ɂ���hit()���Ă�
        if( acceleration_ < 0 )
        {
            // �E���ɂ�����Ƃ�
            if( Collision::collision( kRight, kHead ) <= 64 )
            {
                break_right_x_ = (total_movement_x_ / 64) + 1;
                break_right_y_ = total_movement_y_ / 64;
            }

            // �����ɂ�����Ƃ�
            if( Collision::collision( kLeft, kHead ) <= 64 )
            {
                break_left_x_ = (total_movement_x_ / 64);
                break_left_y_ = total_movement_y_ / 64;
            }

            if( Collision::collision( kRight, kHead ) <= 64 ||
                Collision::collision( kLeft, kHead ) <= 64 )
            {
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

        // �S�[��
        if( total_movement_x_ >= (kSize * 194) + 32 )
        {
            animation_flag_   = true;
            catch_flag_       = false;
            goal_flag_        = false;
            animation_        = 6;
            acceleration_     = 0;
            total_movement_x_ = (kSize * 194) + 32;
        }
    }
    // ����ł���Ƃ�
    else
    {
        // �������Ƃ����o�������S
        if( pos_y_ > kDeadLine )
        {
            return false;
        }

        // status_���}�C�i�X�̎�
        // GameOver Action
        acceleration_ += kGravity;

        // �}���I���΂�
        pos_y_ += acceleration_;
        total_movement_y_ += acceleration_;
    }

    // ���G���Ԑ���
    if( !invincible_ )
    {
        invincible_cnt_++;

        // ���Ԃ������疳�G����
        if( invincible_cnt_ > kInvincible )
        {
            invincible_cnt_ = 0;
            invincible_ = true;
        }
    }

    return true;
}

void Player::draw()
{
    if( extinguish_existence_ )
    {
        break_left_x_ = 0; break_left_y_ = 0;
        break_right_x_ = 0; break_right_y_ = 0;

        if( status_ >= kMario )
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

            if( invincible_ )
                // �E�����}���I�̕`��
                DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_, texture_, TRUE, !direction_ );
            else
                SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 );
            DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_, texture_, TRUE, !direction_ );
            SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 );
        }
        else
        {
            if( invincible_ )
                DrawRectGraph( pos_x_, pos_y_, 0, kSize, kSize, kSize, texture_, TRUE, FALSE );
            else
                DrawRectGraph( pos_x_, pos_y_, 0, kSize, kSize, kSize, texture_, TRUE, FALSE );
        }
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
                animation_++;
            else
                animation_ = 1;
        }
    }
}

void Player::collision()
{
    // �����ɂ���u���b�N������Ƃ�
    if( Collision::footColl() == 1 )
    {
        landing();          // ���n����

        acceleration_ = 0;  // �������x

        int block_line = std::round( static_cast<float>(total_movement_y_) / 64 );
        pos_y_ = (block_line - 4) * kSize;
        total_movement_y_ = block_line * kSize;
    }
    // �����ɉ����Ȃ������Ă���Ƃ�
    else if( Collision::footColl() == 2 )
    {
        // ��ׂȂ��悤�ɂ���
        jumping_ = kNoJump;

        // �}���I����ʊO�ɍs�����Ƃ�
        if( pos_y_ > 670 )
        {
            // gameover
            gameover_flag_ = false;
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
    jumping_ = kJump;
}

void Player::hit()
{
    // ��ւ̉����x�𖳂���
    acceleration_ = 0;

    int block_line = std::round( static_cast<float>(total_movement_y_) / 64 );

    // �v���C���[�̗��ꏊ����̕ӂ̍����ɂ���
    pos_y_ = (block_line - 4) * kSize;
    total_movement_y_ = block_line * kSize;
}

void Player::itemCollision()
{
    // �ŏI�i������Ȃ��Ƃ�
    if( status_ < kFireMario )
    {
        status_ += 1;          // �}���I�ϐg

        if( past_status_ == kMario )
        {
            pos_y_ -= kSize;
            total_movement_y_ -= kSize;
        }

        // �ϐg��̏�Ԃ�ۑ�
        past_status_ = status_;
    }
}

void Player::enemyCollision()
{

    if( past_status_ == kFireMario )
    {
        status_ -= 2;              // �}���I�މ�
        invincible_ = false;       // �}���I���G�ɕς���

        pos_y_ += kSize;
        total_movement_y_ += kSize;
    }
    else if( past_status_ == kSuperMario )
    {
        status_ -= 1;              // �}���I�މ�
        invincible_ = false;       // �}���I���G�ɕς���

        pos_y_ += kSize;
        total_movement_y_ += kSize;
    }
    else
    {
        status_ -= 1;              // �}���I�މ�
        gameover_flag_ = false;
        acceleration_ = -kJumpPower;
    }
    // �ϐg��̏�Ԃ�ۑ�
    past_status_ = status_;
}

void Player::enemyStepon()
{
    // �W�����vRECT�ɐ؂�ւ�
    animation_ = 4;

    // �W�����v���ɃA�j���[�V�����𓮂����Ȃ��悤�ɂ���
    animation_flag_ = false;

    acceleration_ = -kEnemyJump;
}

void Player::Ending()
{
    if( status_ == kMario )
    {
        if( total_movement_y_ < kSize * 11 )
        {
            pos_y_ += kDownSpeed;
            total_movement_y_ += kDownSpeed;

            animation_cnt_++;

            if( animation_cnt_ >= 4 )
            {
                animation_cnt_ = 0;

                if( animation_ == 6 )
                    animation_++;
                else
                    animation_--;
            }
        }
        else if( !catch_flag_ )
        {
            if( !catch_flag_ )
            {
                catch_flag_ = true;
                pos_x_ += kSize;
                total_movement_x_ += kSize;
            }

            direction_ = false;
        }
        else
        {
            if( total_movement_x_ < (kSize * 201) - (kSize / 2 ))
            {
                pos_x_ += 3;
                total_movement_x_ += 3;

                animation();

                if( pos_y_ < kEndLine )
                {
                    acceleration_ += kGravity;
                    pos_y_ += acceleration_;
                    total_movement_y_ += acceleration_;
                }
                else
                {
                    direction_ = true;
                    pos_y_ = kEndLine;
                }
            }
            else
                extinguish_existence_ = false;
        }
    }
    else
        if( total_movement_y_ < kSize * 10 )
        {
            pos_y_ += kDownSpeed;
            total_movement_y_ += kDownSpeed;

            animation_cnt_++;

            if( animation_cnt_ >= 4 )
            {
                animation_cnt_ = 0;

                if( animation_ == 6 )
                    animation_++;
                else
                    animation_--;
            }
        }
        else if( !catch_flag_ )
        {
            if( !catch_flag_ )
            {
                catch_flag_ = true;
                pos_x_ += kSize;
                total_movement_x_ += kSize;
            }

            direction_ = false;
        }
        else
        {
            if( total_movement_x_ < (kSize * 201) - (kSize / 2) )
            {
                pos_x_ += 3;
                total_movement_x_ += 3;

                animation();

                if( pos_y_ < kEndLine - kSize )
                {
                    acceleration_ += kGravity;
                    pos_y_ += acceleration_;
                    total_movement_y_ += acceleration_;
                }
                else
                {
                    direction_ = true;
                    pos_y_ = kEndLine - kSize;
                }
            }
            else
                extinguish_existence_ = false;
        }
}
