#include "player.hpp"

bool Player::initialize()
{
    texture_          = LoadGraph( "Texture/mario_anime.png" );
    data_.player_position.x       = kStartX;
    data_.player_position.y       = kStartY;
  
    // �Q�[���J�n����RECT
    defaultSize( kMario );
 
    // �J�n��data_.player_status��kMario�ȊO�Ȃ�
    if( data_.player_status != kMario )
    {
        data_.player_position.y -= kSize;
        data_.total_position.y -= kSize;
    }
    
    // ���l�̒��̃|�W�V����
    data_.total_position.x = kStartX;
    data_.total_position.y = 832;

    data_.player_status           = kMario;
    past_status_      = data_.player_status;

    data_.scroll_cnt       = 0;            // �E�ɔ����������₵�Ă���

    data_.gameover_flag    = true;         // ���ꂪ�������玀��

    animation_        = 0;            // �����Ă��邾���̏��
    data_.direction        = true;         // �����͉E����

    animation_cnt_    = 0;            // �������Ă��Ȃ��Ƃ��͓����Ȃ�
    animation_flag_   = true;         // �W�����v���Ă���Ƃ��ȊO�͈ړ����A�j���[�V����

    old_right_button_ = true;
    old_left_button_  = true;
    old_down_button_  = true;

    right_button_     = true;
    left_button_      = true;

    acceleration_     = 0;
    jumping_          = kJump;

    data_.invincible_flag       = true;
    invincible_time_  = true;
    invincible_cnt_   = 0;

    data_.goal_flag        = true;
    catch_flag_       = true;
    data_.end_flag = true;

    throw_cnt_ = 0;
    throw_flag_ = true;

    down_cnt_         = 0;

    push_time_jump_ = 0;
    push_time_fire_ = 0;
    push_time_run_  = 0;
    data_.push_squat= 0;

    speed_ = 0;
    speed_up_ = 0;
    speed_down_ = 0;
    sliding_ = true;

    return true;
}

bool Player::update( bool TimeLimit )
{
    if( !data_.goal_flag ) ending();
    else if( data_.gameover_flag )
    {
        if( invincible_time_ )
        {
            // ���Ⴊ�߂�傫�����ǂ���
            if( data_.player_status > kMario && data_.goal_flag )
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
                    rightPush();
                else
                    right_button_ = true;
            }

            if( right_button_ )
            {
                // ������
                if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_LEFT) == 0 || CheckHitKey( KEY_INPUT_A ) == 1 )
                    leftPush();
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
                speed_down_++;

                if( speed_down_ >= 2 )
                {
                    if( speed_ > 0 )
                        speed_--;
                    if( speed_ < 0 )
                        speed_++;

                    speed_down_ = 0;
                }
            }

            // ���Ⴊ��ł��Ȃ�������A�j���[�V����
            if( data_.push_squat == 0 && speed_ != 0 )
                animation();

            if( data_.push_squat == 0 && speed_ == 0 )
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
                    timekeep_squat_ = data_.push_squat;
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
                data_.player_position.y += acceleration_;
                data_.total_position.y += acceleration_;
            }

            // �����x���
            if( acceleration_ >= 20 )
            {
                acceleration_ = 20;
            }

            // ���Ⴊ�ݏ�Ԃ̂ݓ��̈ʒu��������
            if( data_.push_squat == 0 )
            {
                // �}���I�̓�(�������E10������)
                body_[ kRight ][ kHead ][ kX ] = (data_.total_position.x + (kSize - kGather));
                body_[ kRight ][ kHead ][ kY ] = (data_.total_position.y - 1);
                body_[ kLeft ][ kHead ][ kX ] = (data_.total_position.x + kGather);
                body_[ kLeft ][ kHead ][ kY ] = (data_.total_position.y - 1);
            }
            else
            {
                // �}���I�̓�(�������E10������)
                body_[ kRight ][ kHead ][ kX ] = (data_.total_position.x + (kSize - kGather));
                body_[ kRight ][ kHead ][ kY ] = (data_.total_position.y + kSize - 1);
                body_[ kLeft ][ kHead ][ kX ] = (data_.total_position.x + kGather);
                body_[ kLeft ][ kHead ][ kY ] = (data_.total_position.y + kSize - 1);
            }

            // �}���I�̑���
            body_[ kRight ][ kFoot ][ kX ] = (data_.total_position.x + (kSize - kGather));
            body_[ kLeft ][ kFoot ][ kX ] = (data_.total_position.x + kGather);

            // �}���I�̎�
            if( data_.player_status == kMario )
            {
                body_[ kRight ][ kFoot ][ kY ] = (data_.total_position.y + kSize + 1);
                body_[ kLeft ][ kFoot ][ kY ] = (data_.total_position.y + kSize + 1);
            }
            // �}���I�ȊO�̎�
            else
            {
                body_[ kRight ][ kFoot ][ kY ] = (data_.total_position.y + kDoubleSize + 1);
                body_[ kLeft ][ kFoot ][ kY ] = (data_.total_position.y + kDoubleSize + 1);
            }

            // ��֔��ł���Ƃ��ɂ���hit()���Ă�
            if( acceleration_ < 0 )
            {
                // ���Ⴊ�ݎ�
                if( data_.push_squat == 0 )
                {
                    // �E���ɂ�����Ƃ�
                    if( Collision::collision( kRight, kHead ) <= kSize )
                    {
                        data_.break_right.x = (data_.total_position.x / kSize) + 1;
                        data_.break_right.y = data_.total_position.y / kSize;
                    }
                    // �����ɂ�����Ƃ�
                    if( Collision::collision( kLeft, kHead ) <= kSize )
                    {
                        data_.break_left.x = (data_.total_position.x / kSize);
                        data_.break_left.y = data_.total_position.y / kSize;
                    }
                }
                else
                {
                    // �E���ɂ�����Ƃ�
                    if( Collision::collision( kRight, kHead ) <= kSize )
                    {
                        data_.break_right.x = (data_.total_position.x / kSize) + 1;
                        data_.break_right.y = (data_.total_position.y + kSize) / kSize;
                    }
                    // �����ɂ�����Ƃ�
                    if( Collision::collision( kLeft, kHead ) <= kSize )
                    {
                        data_.break_left.x = (data_.total_position.x / kSize);
                        data_.break_left.y = (data_.total_position.y + kSize) / kSize;
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
            if( data_.total_position.x >= (kSize * kGoalPost) + kHalfSize )
            {
                animation_flag_ = true;
                catch_flag_ = false;
                data_.goal_flag = false;
                animation_ = 6;
                acceleration_ = 0;
                data_.total_position.x = (kSize * kGoalPost) + kHalfSize;
            }

            // ���Ԑ����ɂ�鎀�S
            if( !TimeLimit )
            {
                data_.gameover_flag = false;
                acceleration_ = -kJumpPower;
                data_.player_status = kGameover;
            }
        }

        // ���G���Ԑ���
        if( !data_.invincible_flag )
        {
            invincible_cnt_++;

            // �X��g�k��������
            if( invincible_cnt_ > kAnimeMove * kAnimeMove )
                invincible_time_ = true;

            // ���Ԃ������疳�G����
            if( invincible_cnt_ > kInvincible )
            {
                invincible_cnt_ = 0;
                data_.invincible_flag = true;
            }
        }
    }
    // ����ł���Ƃ�
    else
    {
        // �������Ƃ����o�������S
        if( data_.player_position.y > kDeadLine )
            return false;

        // data_.player_status���}�C�i�X�̎�
        // GameOver Action
        acceleration_ += kGravity;

        // �}���I���΂�
        data_.player_position.y += acceleration_;
        data_.total_position.y += acceleration_;
    }

    return true;
}

void Player::draw()
{
    // �S�[���O
    if( data_.end_flag )
    {
        // ���̏�����
        data_.break_left.x = 0; data_.break_left.y = 0;
        data_.break_right.x = 0; data_.break_right.y = 0;

        // ���ʔ͈�(���Ⴊ��ł��Ȃ���)
        if( data_.push_squat == 0 )
        {
            rect_.left = animation_ * kSize;
            rect_.right = kSize;
        }

        // �����Ƃ�
        if( data_.player_status == kGameover )
            defaultSize( kGameover );

        // �t�@�C�A�}���I
        else if( data_.player_status == kFireMario && data_.push_squat == 0 )
            fireMove();

        // RECT�̂��ꂪ�������Ȃ��悤��
        if( data_.player_status == kFireMario && !data_.goal_flag )
            defaultSize( kFireMario );

        // ���G���(������)
        if( !data_.invincible_flag && data_.player_status != kGameover )
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
                    data_.player_position.y += kSize;
                    data_.total_position.y += kSize;
                }
                // �]��O�Ŋ�̎�
                else if( m == 0 && n % 2 == 1 )
                {
                    // Rect��؂�ւ���
                    defaultSize( kSuperMario );

                    // �����𑵂���
                    data_.player_position.y -= kSize;
                    data_.total_position.y -= kSize;
                }
            }
        }

        // �����Ă���Ƃ��������]
        if( animation_ == kSliding )
        {
            if( data_.direction )
                data_.direction = false;
            else
                data_.direction = true;
        }

        // �ʏ�`��
        DrawRectGraph( data_.player_position.x, data_.player_position.y,
            rect_.left, rect_.top, rect_.right, rect_.bottom,
            texture_, TRUE, !data_.direction );

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
    if( animation_flag_ && sliding_ )
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

        int block_line = static_cast<int>(std::round( static_cast<float>(data_.total_position.y) / kSize ));
        data_.player_position.y = (block_line - kControl) * kSize;
        data_.total_position.y = block_line * kSize;
    }
    // �����ɉ����Ȃ������Ă���Ƃ�
    else if( fool_col == 2 )
    {
        // ���Ԃ�ۑ�
        timekeep_squat_ = data_.push_squat;

        // �������ɓ����Ȃ��悤��
        animation_flag_ = false;

        // ��ׂȂ��悤�ɂ���
        jumping_ = kNoJump;

        // �}���I����ʊO�ɍs�����Ƃ�
        if( data_.player_position.y > kFallOut )
        {
            // gameover
            data_.gameover_flag = false;
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

    int block_line = static_cast<int>(std::round( static_cast<float>(data_.total_position.y) / kSize ));

    // �v���C���[�̗��ꏊ����̕ӂ̍����ɂ���
    data_.player_position.y = (block_line - kControl) * kSize;
    data_.total_position.y = block_line * kSize;
}

void Player::itemCollision()
{
    // �ŏI�i������Ȃ��Ƃ�
    if( data_.player_status < kFireMario )
    {
        data_.player_status += 1;          // �}���I�ϐg

        // �X�[�p�[�}���I
        if( data_.player_status == kSuperMario )
            defaultSize( kSuperMario );

        // �t�@�C�A�}���I
        else if( data_.player_status == kFireMario )
            defaultSize( kFireMario );

        // �����𑵂���
        if( past_status_ == kMario )
        {
            data_.player_position.y -= kSize;
            data_.total_position.y -= kSize;
        }

        // �ϐg��̏�Ԃ�ۑ�
        past_status_ = data_.player_status;
    }
}

void Player::enemyCollision()
{
    if( past_status_ > kMario )
    {
        data_.player_status = kMario;           // �}���I�މ�
        data_.invincible_flag = false;        // �}���I���G�ɕς���
        invincible_time_ = false;   // �}���I���G�J�E���g�J�n

        if( data_.push_squat != 0 )
        {
            defaultSize( kMario );
            data_.push_squat = 0;
        }
    }
    else
    {
        data_.player_status = kGameover;        // �}���I���S
        data_.gameover_flag = false;     // �Q�[���I�[�o�[
        acceleration_ = -kJumpPower;// ���˂�A�N�V����
    }

    past_status_ = data_.player_status;         // �ϐg��̏�Ԃ�ۑ�
}

void Player::enemyStepon()
{    
    // ���Ⴊ��ł��Ȃ���
    if(data_.push_squat == 0)
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
    if( data_.player_status == kMario )
    {
        if( data_.total_position.y < (kSize * 11 + kHalfSize) )
        {
            // �������ƃ|�X�g����~���
            data_.player_position.y += kDownSpeed;
            data_.total_position.y += kDownSpeed;

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
                data_.player_position.x += kSize;
                data_.total_position.x += kSize;
            }

            data_.direction = false;
        }
        // ���֌������ĕ����o��
        else if( down_cnt_ >= kTurnCnt )
        {
            if( data_.total_position.x < (kSize * kEntrance) - kHalfSize )
            {
                data_.player_position.x += 3;
                data_.total_position.x += 3;

                animation();

                if( data_.player_position.y < kEndLine )
                {
                    acceleration_ += kGravity;
                    data_.player_position.y += acceleration_;
                    data_.total_position.y += acceleration_;
                }
                else
                {
                    data_.direction = true;
                    data_.player_position.y = kEndLine;
                }
            }
            else
                // ������
                data_.end_flag = false;
        }
    }
    // �̂��}���I�ȊO�̎�
    else
        if( data_.total_position.y < (kDecuple + kHalfSize) )
        {
            // �|�X�g����~���
            data_.player_position.y += kDownSpeed;
            data_.total_position.y += kDownSpeed;

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
                data_.player_position.x += kSize;
                data_.total_position.x += kSize;
            }

            data_.direction = false;
        }
        // ���֌������ĕ���
        else if(down_cnt_ >= kTurnCnt)
        {
            if( data_.total_position.x < (kSize * kEntrance) - kHalfSize )
            {
                data_.player_position.x += 3;
                data_.total_position.x += 3;

                // �����A�j���[�V����
                animation();

                if( data_.player_position.y < kEndLine - kSize )
                {
                    acceleration_ += kGravity;
                    data_.player_position.y += acceleration_;
                    data_.total_position.y += acceleration_;
                }
                else
                {
                    data_.direction = true;
                    data_.player_position.y = kEndLine - kSize;
                }
            }
            else
                // �̂̓�����
                data_.end_flag = false;
        }
}

void Player::rightCheck()
{
    // �̂̏㉺�̊m�F
    body_[ kRight ][ kShoulder ][ kX ] = (data_.total_position.x + kSize + 1);
    body_[ kRight ][ kShoulder ][ kY ] = (data_.total_position.y);

    body_[ kRight ][ kHands ][ kX ] = (data_.total_position.x + kSize + 1);
    // data_.player_status��kMario�̎�
    if( data_.player_status == kMario )
        body_[ kRight ][ kHands ][ kY ] = (data_.total_position.y + kSize - 1);
    else
        body_[ kRight ][ kHands ][ kY ] = (data_.total_position.y + kDoubleSize - 1);


    // �����蔻��̂Ȃ��u���b�N�̂Ƃ�
    if( Collision::sideColl( kRight ) == true )
    {
        // kSuperMario�ȏ�̎��̂̐^�񒆂����蔲���Ȃ��悤�Ɋm�F
        if( data_.player_status >= kSuperMario )
        {
            // �̂̉E����o�^
            body_[ kRight ][ kShoulder ][ kX ] = (data_.total_position.x + kSize + 1);
            body_[ kRight ][ kShoulder ][ kY ] = (data_.total_position.y + kSize);
        }

        // ������x�����蔻����m�F����
        if( Collision::sideColl( kRight ) == true )
        {
            data_.player_position.x += speed_;
            data_.total_position.x += speed_;

            // pos_x_ �Z���^�[�𒴂���Ƃ�
            if( data_.player_position.x > kEndLine )
            {
                data_.scroll_cnt = data_.total_position.x - kEndLine;
                data_.player_position.x = kEndLine;
            }
        }
    }
}

void Player::leftCheck()
{
    // ��Ɨ��T�C�h�͕ύX�Ȃ�
    body_[ kLeft ][ kShoulder ][ kX ] = (data_.total_position.x - 1);
    body_[ kLeft ][ kShoulder ][ kY ] = (data_.total_position.y);

    body_[ kLeft ][ kHands ][ kX ] = (data_.total_position.x - 1);

    // ���̈ʒu������Ԃɉ����ĕύX����
    if( data_.player_status == kMario )
        body_[ kLeft ][ kHands ][ kY ] = (data_.total_position.y + kSize - 1);
    else
        body_[ kLeft ][ kHands ][ kY ] = (data_.total_position.y + kDoubleSize - 1);

    // �}���I�̍����ɏՓ˂���u���b�N���Ȃ��Ƃ�
    if( Collision::sideColl( kLeft ) == true )
    {
        // ��Ԃ��X�[�p�[�}���I����̎�
        if( data_.player_status >= kSuperMario )
        {
            // �̂̍�����o�^
            body_[ kLeft ][ kShoulder ][ kX ] = (data_.total_position.x - 1);
            body_[ kLeft ][ kShoulder ][ kY ] = (data_.total_position.y + kSize);
        }

        // ������x�����蔻����m�F����
        if( Collision::sideColl( kLeft ) == true )
        {
                // �|�W�V�����[����荶�̎�
                if( data_.player_position.x <= 0 )
                    data_.player_position.x = 0;
                else
                {
                    data_.player_position.x += speed_;
                    data_.total_position.x += speed_;
                }
        }
    }
}

// ���Ⴊ�ݓ���
void Player::squat()
{
    // ���������ꂽ�Ƃ�
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_DOWN) == 0 || CheckHitKey( KEY_INPUT_S ) == 1 )
        data_.push_squat++;
    else
    {
            defaultSize( data_.player_status );
            data_.push_squat = 0;
    }

    // �W�����v�����u�Ԃ̏�Ԃ��L�[�v
    if( !animation_flag_ )
        data_.push_squat = timekeep_squat_;

    // ���Ⴊ�݂������ꂽ�Ƃ�RECT�؂�ւ�
    if( data_.push_squat >= 1 )
    {
        if( data_.player_status == kSuperMario )
            rect_.top = kSextuple;

        else if( data_.player_status == kFireMario )
            rect_.top = kDecuple;

        rect_.left = 0;
        rect_.right = kSize;
        rect_.bottom = kDoubleSize;
    }
}

void Player::fireMove()
{
    // Status FireMario
    if( data_.goal_flag )
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
    data_.direction = true;         // �������E�����ɕς���
    right_button_ = false;     // �����Ă���(�g���b�J�[) 

    if( data_.push_squat == 0 )
    {           
        speed_up_++;

        // �_�b�V��������Ă��鎞
        if( push_time_run_ != 0 )
        {
            if( speed_up_ >= 2 )
            {
                if( speed_ < kDashSpeed )
                    speed_++;

                if( speed_ < 0 )
                {
                    sliding_ = false;
                    animation_ = kSliding;
                }
                else
                    sliding_ = true;

                speed_up_ = 0;
            }
        }
        // �_�b�V��������Ă��Ȃ���
        else
        {
            if( speed_ > kSpeed )
                speed_ = kSpeed;

            if( speed_up_ >= 2 )
            {
                if( speed_ < kSpeed )
                    speed_++;

                if( speed_ < 0 )
                {
                    sliding_ = false;
                    animation_ = kSliding;
                }
                else
                    sliding_ = true;

                speed_up_ = 0;
            }
        }
    }
    else
    {
        speed_down_++;

        if( speed_down_ >= 2 )
        {
            if( speed_ > 0 )
                speed_--;
            if( speed_ < 0 )
                speed_++;

            speed_down_ = 0;
        }
    }
}

void Player::leftPush()
{
    data_.direction = false;        // �������������ɕς���
    left_button_ = false;      // �����Ă���(�g���b�J�[)

    if( data_.push_squat == 0 )
    {
        speed_up_++;

        // �_�b�V��������Ă��鎞
        if( push_time_run_ != 0 )
        {
            if( speed_up_ >= 2 )
            {
                if( speed_ > -kDashSpeed )
                    speed_--;

                if( speed_ > 0 )
                {
                    sliding_ = false;
                    animation_ = kSliding;
                }
                else
                    sliding_ = true;

                speed_up_ = 0;
            }
        }
        // �_�b�V��������Ă��Ȃ���
        else
        {
            if( speed_ < -kSpeed )
                speed_ = -kSpeed;

            if( speed_up_ >= 2 )
            {
                if( speed_ > -kSpeed )
                    speed_--;

                if(speed_ > 0)
                {
                    sliding_ = false;
                    animation_ = kSliding;
                }
                else
                    sliding_ = true;

                speed_up_ = 0;
            }
        }
    }
    // ���Ⴊ��ł��鎞
    else
    {
        speed_down_++;

        if( speed_down_ >= 2 )
        {
            if( speed_ > 0 )
                speed_--;
            if( speed_ < 0 )
                speed_++;

            speed_down_ = 0;
        }
    }
}

PlayerData Player::getData()
{
    return data_;
}