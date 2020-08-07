#include "player.hpp"

bool Player::initialize()
{
    texture_          = LoadGraph( "Texture/mario_anime.png" );
    position_.x       = kStartX;
    position_.y       = kStartY;
  
    // �Q�[���J�n����RECT
    defaultSize( kMario );
 
    // �J�n��status_��kMario�ȊO�Ȃ�
    if( status_ != kMario )
    {
        position_.y -= kSize;
        total_move_.y -= kSize;
    }

    
    // ���l�̒��̃|�W�V����
    total_move_.x = kStartX;
    total_move_.y = 832;

    status_           = kMario;
    past_status_      = status_;

    scroll_cnt_       = 0;            // �E�ɔ����������₵�Ă���

    gameover_flag_    = true;         // ���ꂪ�������玀��

    animation_        = 0;            // �����Ă��邾���̏��
    direction_        = true;         // �����͉E����

    animation_cnt_    = 0;            // �������Ă��Ȃ��Ƃ��͓����Ȃ�
    animation_flag_   = true;         // �W�����v���Ă���Ƃ��ȊO�͈ړ����A�j���[�V����

    old_right_button_ = true;
    old_left_button_  = true;
    old_down_button_  = true;

    right_button_     = true;
    left_button_      = true;

    acceleration_     = 0;
    jumping_          = kJump;

    invincible_       = true;
    invincible_time_  = true;
    invincible_cnt_   = 0;

    goal_flag_        = true;
    catch_flag_       = true;
    extinguish_existence_ = true;

    throw_cnt_ = 0;
    throw_flag_ = true;

    down_cnt_         = 0;

    push_time_jump_ = 0;
    push_time_fire_ = 0;
    push_time_run_  = 0;
    push_time_squat_= 0;
    speed_ = 0;

    return true;
}

bool Player::update( bool TimeLimit )
{
    if( !goal_flag_ ) ending();
    else if( gameover_flag_ )
    {
        if( invincible_time_ )
        {
            // ���Ⴊ�߂�傫�����ǂ���
            if( status_ > kMario && goal_flag_ )
                squat();

            // �_�b�V���{�^������
            if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4) == 0 || CheckHitKey( KEY_INPUT_B ) == 1 )
                push_time_run_++;
            else
                push_time_run_ = 0;

            if( left_button_ )
            {
                // �E����
                if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_RIGHT) == 0 || CheckHitKey( KEY_INPUT_D ) == 1 )
                {
                    rightPush();

                    // ���Ⴊ��ł��Ȃ�������A�j���[�V����
                    if( push_time_squat_ == 0 )
                        animation();
                }
                else
                    right_button_ = true;
            }

            if( right_button_ )
            {
                // ������
                if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_LEFT) == 0 || CheckHitKey( KEY_INPUT_A ) == 1 )
                {
                    leftPush();
                 
                    // ���Ⴊ��ł��Ȃ�������A�j���[�V����
                    if( push_time_squat_ == 0 )
                        animation();
                }
                else
                    left_button_ = true;
            }

            // �E�ւ̈ړ���
            if( speed_ > 0 )
                rightCheck();

            // ���ւ̈ړ���
            if( speed_ < 0 )
                leftCheck();

            // �X�s�[�h�͂��邪�{�^���͉����Ă��Ȃ�����0�ɂ���
            if( speed_ != 0 && right_button_ && left_button_ )
            {
                if( speed_ > 0 )
                    speed_--;
                if( speed_ < 0 )
                    speed_++;
            }

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
            if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_B) == 0 || CheckHitKey( KEY_INPUT_SPACE ) == 1 )
                push_time_jump_++;
            else
                push_time_jump_ = 0;

            // �������
            if( push_time_jump_ == 1 )
            {
                if( jumping_ == kJump )
                {
                    timekeep_squat_ = push_time_squat_;
                    jumping_ = kNoJump;
                    acceleration_ = -kJumpPower;

                    // �W�����v���ɃA�j���[�V�����𓮂����Ȃ��悤�ɂ���
                    animation_flag_ = false;

                    // �W�����vRECT�ɐ؂�ւ�
                    // kMario��Ԃ̎��̂ݗL��
                    if( timekeep_squat_ == 0 )
                        animation_ = 4;
                }
            }

            // �W�����v���������d�͂�������
            if( jumping_ == kNoJump )
            {
                acceleration_ += kGravity;

                // �}���I���΂�
                position_.y += acceleration_;
                total_move_.y += acceleration_;
            }

            // �����x���
            if( acceleration_ >= 20 )
            {
                acceleration_ = 20;
            }

            // ���Ⴊ�ݏ�Ԃ̂ݓ��̈ʒu��������
            if( push_time_squat_ == 0 )
            {
                // �}���I�̓�(�������E10������)
                body_[ kRight ][ kHead ][ kX ] = (total_move_.x + (kSize - kGather));
                body_[ kRight ][ kHead ][ kY ] = (total_move_.y - 1);
                body_[ kLeft ][ kHead ][ kX ] = (total_move_.x + kGather);
                body_[ kLeft ][ kHead ][ kY ] = (total_move_.y - 1);
            }
            else
            {
                // �}���I�̓�(�������E10������)
                body_[ kRight ][ kHead ][ kX ] = (total_move_.x + (kSize - kGather));
                body_[ kRight ][ kHead ][ kY ] = (total_move_.y + kSize - 1);
                body_[ kLeft ][ kHead ][ kX ] = (total_move_.x + kGather);
                body_[ kLeft ][ kHead ][ kY ] = (total_move_.y + kSize - 1);
            }

            // �}���I�̑���
            body_[ kRight ][ kFoot ][ kX ] = (total_move_.x + (kSize - kGather));
            body_[ kLeft ][ kFoot ][ kX ] = (total_move_.x + kGather);

            // �}���I�̎�
            if( status_ == kMario )
            {
                body_[ kRight ][ kFoot ][ kY ] = (total_move_.y + kSize + 1);
                body_[ kLeft ][ kFoot ][ kY ] = (total_move_.y + kSize + 1);
            }
            // �}���I�ȊO�̎�
            else
            {
                body_[ kRight ][ kFoot ][ kY ] = (total_move_.y + kDoubleSize + 1);
                body_[ kLeft ][ kFoot ][ kY ] = (total_move_.y + kDoubleSize + 1);
            }

            // ��֔��ł���Ƃ��ɂ���hit()���Ă�
            if( acceleration_ < 0 )
            {
                // ���Ⴊ�ݎ�
                if( push_time_squat_ == 0 )
                {
                    // �E���ɂ�����Ƃ�
                    if( Collision::collision( kRight, kHead ) <= kSize )
                    {
                        break_right_.x = (total_move_.x / kSize) + 1;
                        break_right_.y = total_move_.y / kSize;
                    }
                    // �����ɂ�����Ƃ�
                    if( Collision::collision( kLeft, kHead ) <= kSize )
                    {
                        break_left_.x = (total_move_.x / kSize);
                        break_left_.y = total_move_.y / kSize;
                    }
                }
                else
                {
                    // �E���ɂ�����Ƃ�
                    if( Collision::collision( kRight, kHead ) <= kSize )
                    {
                        break_right_.x = (total_move_.x / kSize) + 1;
                        break_right_.y = (total_move_.y + kSize) / kSize;
                    }
                    // �����ɂ�����Ƃ�
                    if( Collision::collision( kLeft, kHead ) <= kSize )
                    {
                        break_left_.x = (total_move_.x / kSize);
                        break_left_.y = (total_move_.y + kSize) / kSize;
                    }
                }

                // ���̏�ɂ���u���b�N�𒲂ׂ�
                if( Collision::collision( kRight, kHead ) <= kSize ||
                    Collision::collision( kLeft, kHead ) <= kSize )
                {
                    // �����Ԃ����Ƃ��̔���
                    hit();
                }
            }
            // ��֔�ԉ������Ȃ��Ȃ����Ƃ��ɉ��̔�������n�߂�
            else
                // �����̏Փ˔���
                collision();

            // �S�[��
            if( total_move_.x >= (kSize * kGoalPost) + kHalfSize )
            {
                animation_flag_ = true;
                catch_flag_ = false;
                goal_flag_ = false;
                animation_ = 6;
                acceleration_ = 0;
                total_move_.x = (kSize * kGoalPost) + kHalfSize;
            }

            // ���Ԑ����ɂ�鎀�S
            if( !TimeLimit )
            {
                gameover_flag_ = false;
                acceleration_ = -kJumpPower;
                status_ = kGameover;
            }
        }

        // ���G���Ԑ���
        if( !invincible_ )
        {
            invincible_cnt_++;

            // �X��g�k��������
            if( invincible_cnt_ > kAnimeMove * kAnimeMove )
                invincible_time_ = true;

            // ���Ԃ������疳�G����
            if( invincible_cnt_ > kInvincible )
            {
                invincible_cnt_ = 0;
                invincible_ = true;
            }
        }
    }
    // ����ł���Ƃ�
    else
    {
        // �������Ƃ����o�������S
        if( position_.y > kDeadLine )
            return false;

        // status_���}�C�i�X�̎�
        // GameOver Action
        acceleration_ += kGravity;

        // �}���I���΂�
        position_.y += acceleration_;
        total_move_.y += acceleration_;
    }

    return true;
}

void Player::draw()
{
    // �S�[���O
    if( extinguish_existence_ )
    {
        // ���̏�����
        break_left_.x = 0; break_left_.y = 0;
        break_right_.x = 0; break_right_.y = 0;

        // ���ʔ͈�(���Ⴊ��ł��Ȃ���)
        if( push_time_squat_ == 0 )
        {
            rect_.left = animation_ * kSize;
            rect_.right = kSize;
        }

        // �����Ƃ�
        if( status_ == kGameover )
            defaultSize( kGameover );

        // �t�@�C�A�}���I
        else if( status_ == kFireMario && push_time_squat_ == 0 )
            fireMove();

        // RECT�̂��ꂪ�������Ȃ��悤��
        if( status_ == kFireMario && !goal_flag_ )
            defaultSize( kFireMario );

        // ���G���(������)
        if( !invincible_ && status_ != kGameover )
        {
            // �T�C�Y�ϊ�
            SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 );

            // �傫���A���������J��Ԃ�
            int n = invincible_cnt_ / kAnimeMove;
            int m = invincible_cnt_ % kAnimeMove;

            // 8��s���܂ŌJ��Ԃ�
            if( invincible_cnt_ <= kAnimeMove * kAnimeMove )
            {
                // �]��O�ŋ����̎�
                if( m == 0 && n % 2 == 0 )
                {
                    // Rect��؂�ւ���
                    defaultSize( kMario );

                    // �����𑵂���
                    position_.y += kSize;
                    total_move_.y += kSize;
                }
                // �]��O�Ŋ�̎�
                else if( m == 0 && n % 2 == 1 )
                {
                    // Rect��؂�ւ���
                    defaultSize( kSuperMario );

                    // �����𑵂���
                    position_.y -= kSize;
                    total_move_.y -= kSize;
                }
            }
        }

        // �ʏ�`��
        DrawRectGraph( position_.x, position_.y,
            rect_.left, rect_.top, rect_.right, rect_.bottom,
            texture_, TRUE, !direction_ );

        // ��Ԃ�߂�
        SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 );
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

        if( animation_cnt_ >= 4 )
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
    int fool_col = Collision::footColl();

    // �����ɂ���u���b�N������Ƃ�
    if( fool_col == 1 )
    {
        landing();          // ���n����

        acceleration_ = 0;  // �������x

        int block_line = static_cast<int>(std::round( static_cast<float>(total_move_.y) / kSize ));
        position_.y = (block_line - kControl) * kSize;
        total_move_.y = block_line * kSize;
    }
    // �����ɉ����Ȃ������Ă���Ƃ�
    else if( fool_col == 2 )
    {
        // ��ׂȂ��悤�ɂ���
        jumping_ = kNoJump;

        // �}���I����ʊO�ɍs�����Ƃ�
        if( position_.y > kFallOut )
        {
            // gameover
            gameover_flag_ = false;
        }
    }
}

// ���n�����^�C�~���O
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

    int block_line = static_cast<int>(std::round( static_cast<float>(total_move_.y) / kSize ));

    // �v���C���[�̗��ꏊ����̕ӂ̍����ɂ���
    position_.y = (block_line - kControl) * kSize;
    total_move_.y = block_line * kSize;
}

void Player::itemCollision()
{
    // �ŏI�i������Ȃ��Ƃ�
    if( status_ < kFireMario )
    {
        status_ += 1;          // �}���I�ϐg

        // �X�[�p�[�}���I
        if( status_ == kSuperMario )
            defaultSize( kSuperMario );

        // �t�@�C�A�}���I
        else if( status_ == kFireMario )
            defaultSize( kFireMario );

        // �����𑵂���
        if( past_status_ == kMario )
        {
            position_.y -= kSize;
            total_move_.y -= kSize;
        }

        // �ϐg��̏�Ԃ�ۑ�
        past_status_ = status_;
    }
}

void Player::enemyCollision()
{
    if( past_status_ > kMario )
    {
        status_ = kMario;           // �}���I�މ�
        invincible_ = false;        // �}���I���G�ɕς���
        invincible_time_ = false;   // �}���I���G�J�E���g�J�n

        if( push_time_squat_ != 0 )
        {
            defaultSize( kMario );
            push_time_squat_ = 0;
        }
    }
    else
    {
        status_ = kGameover;        // �}���I���S
        gameover_flag_ = false;     // �Q�[���I�[�o�[
        acceleration_ = -kJumpPower;// ���˂�A�N�V����
    }

    past_status_ = status_;         // �ϐg��̏�Ԃ�ۑ�
}

void Player::enemyStepon()
{    
    // ���Ⴊ��ł��Ȃ���
    if(push_time_squat_ == 0)
    animation_ = 4;

    // �W�����v���ɃA�j���[�V�����𓮂����Ȃ��悤�ɂ���
    animation_flag_ = false;

    acceleration_ = -kEnemyJump;
}

// �S�[�����������̏���
void Player::ending()
{        
    // �������]�܂ł̃J�E���g
    down_cnt_++;

    // ��Ԃ��}���I�̎�
    if( status_ == kMario )
    {
        if( total_move_.y < (kSize * 11 + kHalfSize) )
        {
            // �������ƃ|�X�g����~���
            position_.y += kDownSpeed;
            total_move_.y += kDownSpeed;

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
        // �~�肫����������ς��|�X�g�̌��������֍s��
        else if( !catch_flag_ && down_cnt_ >= kDownCnt )
        {
            if( !catch_flag_ )
            {
                catch_flag_ = true;
                position_.x += kSize;
                total_move_.x += kSize;
            }

            direction_ = false;
        }
        // ���֌������ĕ����o��
        else if( down_cnt_ >= kTurnCnt )
        {
            if( total_move_.x < (kSize * kEntrance) - kHalfSize )
            {
                position_.x += 3;
                total_move_.x += 3;

                animation();

                if( position_.y < kEndLine )
                {
                    acceleration_ += kGravity;
                    position_.y += acceleration_;
                    total_move_.y += acceleration_;
                }
                else
                {
                    direction_ = true;
                    position_.y = kEndLine;
                }
            }
            else
                // ������
                extinguish_existence_ = false;
        }
    }
    // �̂��}���I�ȊO�̎�
    else
        if( total_move_.y < (kDecuple + kHalfSize) )
        {
            // �|�X�g����~���
            position_.y += kDownSpeed;
            total_move_.y += kDownSpeed;

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
        // ������ς��|�X�g�̌���������
        else if( !catch_flag_ && down_cnt_ >= kDownCnt )
        {
            if( !catch_flag_ )
            {
                catch_flag_ = true;
                position_.x += kSize;
                total_move_.x += kSize;
            }

            direction_ = false;
        }
        // ���֌������ĕ���
        else if(down_cnt_ >= kTurnCnt)
        {
            if( total_move_.x < (kSize * kEntrance) - kHalfSize )
            {
                position_.x += 3;
                total_move_.x += 3;

                // �����A�j���[�V����
                animation();

                if( position_.y < kEndLine - kSize )
                {
                    acceleration_ += kGravity;
                    position_.y += acceleration_;
                    total_move_.y += acceleration_;
                }
                else
                {
                    direction_ = true;
                    position_.y = kEndLine - kSize;
                }
            }
            else
                // �̂̓�����
                extinguish_existence_ = false;
        }
}

void Player::rightCheck()
{
    // �̂̏㉺�̊m�F
    body_[ kRight ][ kShoulder ][ kX ] = (total_move_.x + kSize + 1);
    body_[ kRight ][ kShoulder ][ kY ] = (total_move_.y);

    body_[ kRight ][ kHands ][ kX ] = (total_move_.x + kSize + 1);
    // status_��kMario�̎�
    if( status_ == kMario )
        body_[ kRight ][ kHands ][ kY ] = (total_move_.y + kSize - 1);
    else
        body_[ kRight ][ kHands ][ kY ] = (total_move_.y + kDoubleSize - 1);


    // �����蔻��̂Ȃ��u���b�N�̂Ƃ�
    if( Collision::sideColl( kRight ) == true )
    {
        // kSuperMario�ȏ�̎��̂̐^�񒆂����蔲���Ȃ��悤�Ɋm�F
        if( status_ >= kSuperMario )
        {
            // �̂̉E����o�^
            body_[ kRight ][ kShoulder ][ kX ] = (total_move_.x + kSize + 1);
            body_[ kRight ][ kShoulder ][ kY ] = (total_move_.y + kSize);
        }

        // ������x�����蔻����m�F����
        if( Collision::sideColl( kRight ) == true )
        {
            position_.x += speed_;
            total_move_.x += speed_;

            // pos_x_ �Z���^�[�𒴂���Ƃ�
            if( position_.x > kEndLine )
            {
                scroll_cnt_ = total_move_.x - kEndLine;
                position_.x = kEndLine;
            }
        }
    }
}

void Player::leftCheck()
{
    // ��Ɨ��T�C�h�͕ύX�Ȃ�
    body_[ kLeft ][ kShoulder ][ kX ] = (total_move_.x - 1);
    body_[ kLeft ][ kShoulder ][ kY ] = (total_move_.y);

    body_[ kLeft ][ kHands ][ kX ] = (total_move_.x - 1);

    // ���̈ʒu������Ԃɉ����ĕύX����
    if( status_ == kMario )
        body_[ kLeft ][ kHands ][ kY ] = (total_move_.y + kSize - 1);
    else
        body_[ kLeft ][ kHands ][ kY ] = (total_move_.y + kDoubleSize - 1);

    // �}���I�̍����ɏՓ˂���u���b�N���Ȃ��Ƃ�
    if( Collision::sideColl( kLeft ) == true )
    {
        // ��Ԃ��X�[�p�[�}���I����̎�
        if( status_ >= kSuperMario )
        {
            // �̂̍�����o�^
            body_[ kLeft ][ kShoulder ][ kX ] = (total_move_.x - 1);
            body_[ kLeft ][ kShoulder ][ kY ] = (total_move_.y + kSize);
        }

        // ������x�����蔻����m�F����
        if( Collision::sideColl( kLeft ) == true )
        {
                // �|�W�V�����[����荶�̎�
                if( position_.x <= 0 )
                    position_.x = 0;
                else
                {
                    position_.x += speed_;
                    total_move_.x += speed_;
                }
        }
    }
}

// ���Ⴊ�ݓ���
void Player::squat()
{
    // ���������ꂽ�Ƃ�
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_DOWN) == 0 || CheckHitKey( KEY_INPUT_S ) == 1 )
        push_time_squat_++;
    else
    {
            defaultSize( status_ );
            push_time_squat_ = 0;
    }

    // �W�����v�����u�Ԃ̏�Ԃ��L�[�v
    if( !animation_flag_ )
        push_time_squat_ = timekeep_squat_;

    // ���Ⴊ�݂������ꂽ�Ƃ�RECT�؂�ւ�
    if( push_time_squat_ >= 1 )
    {
        if( status_ == kSuperMario )
            rect_.top = kSextuple;

        else if( status_ == kFireMario )
            rect_.top = kDecuple;

        rect_.left = 0;
        rect_.right = kSize;
        rect_.bottom = kDoubleSize;
    }
}

void Player::fireMove()
{
    // Status FireMario
    if( goal_flag_ )
    {
        if( throw_flag_ )
        {
            if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4) == 0 || CheckHitKey( KEY_INPUT_B ) == 1 )
                push_time_fire_++;
            else
                push_time_fire_ = 0;
        }

        // �t�@�C�A�{�[���𓊂���{�^���̏�����͎�
        if( push_time_fire_ == 1 )
            throw_flag_ = false;

        // �����邪�����ꂽ�Ƃ�
        if( !throw_flag_ )
        {
            throw_cnt_++;

            // ������؂���͈�
            rect_.left = kQuadruple;
            rect_.right = kSize;
            rect_.top = kDecuple;
            rect_.bottom = kDoubleSize;
        }
        else
            defaultSize( kFireMario );

        // �A�����˂�h�~����
        if( throw_cnt_ >= kStopper )
        {
            throw_cnt_ = 0;
            throw_flag_ = true;
        }
    }
}

// RECT�o�^
void Player::defaultSize( int Status )
{
    // �Q�[���I�[�o�[
    if( Status == kGameover )
    {        
        rect_.left   = 0;
        rect_.right  = kSize;
        rect_.top    = kSize;
        rect_.bottom = kSize;
    }
    // �}���I
    else if( Status == kMario )
    {
        rect_.top    = 0;
        rect_.bottom = kSize;
    }
    // �X�[�p�[�}���I
    else if( Status == kSuperMario )
    { 
        rect_.top = kQuadruple;
        rect_.bottom = kDoubleSize;
    }
    // �t�@�C�A�}���I
    else if( Status == kFireMario )
    {
        rect_.top = kOctuple;
        rect_.bottom = kDoubleSize;
    }
}

void Player::rightPush()
{
    direction_ = true;         // �������E�����ɕς���
    right_button_ = false;     // �����Ă���(�g���b�J�[) 

    if( push_time_squat_ == 0 )
    {
        // �_�b�V��������Ă��鎞
        if( push_time_run_ != 0 )
        {
            if( speed_ < kDashSpeed )
                speed_++;
        }
        // �_�b�V��������Ă��Ȃ���
        else
        {
            if( speed_ > kSpeed )
                speed_ = kSpeed;

            if( speed_ < kSpeed )
                speed_++;
        }
    }
    else
    {
        if( speed_ > 0 )
            speed_--;

        if( speed_ < 0 )
            speed_++;
    }
}

void Player::leftPush()
{
    direction_ = false;        // �������������ɕς���
    left_button_ = false;      // �����Ă���(�g���b�J�[)

    if( push_time_squat_ == 0 )
    {
        // �_�b�V��������Ă��鎞
        if( push_time_run_ != 0 )
        {
            if( speed_ > -kDashSpeed )
                speed_--;
        }
        // �_�b�V��������Ă��Ȃ���
        else
        {
            if( speed_ < -kSpeed )
                speed_ = -kSpeed;

            if( speed_ > -kSpeed )
                speed_--;
        }
    }
    // ���Ⴊ��ł��鎞
    else
    {
        if( speed_ < 0 )
            speed_++;

        if( speed_ > 0 )
            speed_--;
    }
}