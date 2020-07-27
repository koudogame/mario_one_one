#include "collision.hpp"

class Player :
    public Collision
{
public:
    const int kSpeed      = 6;      // �����Ă���Ƃ��̑��x
    const int kDownSpeed  = 6;      // �S�[�������Ƃ�������X�s�[�h
    const int kDashSpeed  = 10;     // �_�b�V�����Ă���Ƃ��̑��x
    const int kEnemyJump  = 15;     // �G�𓥂񂾎��̃W�����v��
    const int kStopper    = 16;     // �A�˖h�~�X�g�b�p�[
    const int kJumpPower  = 24;     // �W�����v�{�^�����̃W�����v��
    const int kDownCnt    = 66;     // �͂�ł���̑҂�����
    const int kTurnCnt    = 90;     // �������]�����邽�߂̎���
    const int kInvincible = 120;    // ���G��������
    const int kSkyBlue    = 191;    // �w�i�̉����Ȃ������}�b�v�`�b�vID
    const int kGoalPost   = 194;    // �S�[���|�X�g
    const int kStartX     = 256;    // �������WX
    const int kStartY     = 576;    // �������WY
    const int kEndLine    = 576;    // ��ʂ̒��S
    const int kDeadLine   = 800;    // ���̐��l��艺�͎���

    Player( Field* field ) : Collision( field ) {};
    bool initialize();
    bool update();
    void draw();
    void finalize();

    void animation();               // �}���I�̃A�j���[�V����
    void collision();               // �����̏Փ˔�����s��
    void landing();                 // ���n�����Ƃ��̏������s��
    void hit();                     // �����Ԃ����Ƃ��̔���
    void itemCollision();           // �A�C�e���ɓ��������Ƃ�
    void enemyCollision();          // �Ԃ������Ƃ��̏���
    void enemyStepon();             // ���݂����Ƃ��̏���      
    void ending();                  // �G���f�B���O����
    void rightCheck();              // �̂̉E����o�^���ă`�F�b�N����֐�
    void leftCheck();               // �̂̍�����o�^���ă`�F�b�N����֐�

    /*�w�i�̕`��𗬂����l*/
    inline int getScrollCnt() { return scroll_cnt_; }

    /*�}���I�̏�Ԃ�field�ɂ��m�点��*/
    inline int getStatus() { return status_; }

    /*���G��Ԃ��m�F*/
    inline bool getInvincible() { return invincible_; }

    /*�S�[�����Ă��邩*/
    inline bool getGoal() { return goal_flag_; }

    // �����ɉ����ēn��
    inline int getDirection() 
    {
        if( direction_ ) return 1;
        else return -1;
    }

    /*�}���I�̉�ʍ��W��n��*/
    inline int getPosX() { return pos_x_; }
    inline int getPosY() { return pos_y_; }

    /*�}���I�̃|�W�V������n��*/
    inline int getPositionX() { return total_movement_x_; }
    inline int getPositionY() { return total_movement_y_; }

    /*���̓��������Ƃ�*/
    inline int getBreakLeftX() { return break_left_x_; }        /*�����̔z��x*/
    inline int getBreakLeftY() { return break_left_y_; }        /*�����̔z��y*/
    inline int getBreakRightX() { return break_right_x_; }      /*�E���̔z��x*/
    inline int getBreakRightY() { return break_right_y_; }      /*�E���̔z��y*/
    
    inline bool getEnd() { return extinguish_existence_; }      /*���݂���������*/
    inline bool getGameover() { return gameover_flag_; }        /*����ł��邩*/

private:
    int texture_;              // �e�N�X�`���n���h��

    int total_movement_x_;     // �����ړ���x
    int total_movement_y_;     // �����ړ���y

    int pos_x_;                // ���Wx
    int pos_y_;                // ���Wy 

    
    int left_;                 // SrcX
    int top_;                  // SrcY

    int right_;                // Width
    int bottom_;               // Height

    int status_;               // �}���I�̏��
    int past_status_;          // �}���I�̉ߋ��̏��

    int scroll_cnt_;           // �������}���I���������Ƃ��ɃX�N���[��

    bool gameover_flag_;       // true : �����Ă���, false : ����ł���

    int animation_;            // �����Ă���Ƃ��̐؂���͈�
    bool direction_;           // true : �E����, false : ������

    int animation_cnt_;        // ���������߂̃A�j���[�V������������ 
    bool animation_flag_;      // true : ����, false : �����Ȃ�

    // �ߋ��̏�Ԃ�ۑ�����
    bool old_right_button_;    // true : �����ĂȂ�, false : �����Ă��܂�
    bool old_left_button_;     // true : �����ĂȂ�, false : �����Ă��܂�

    // ���܂̏�Ԃ�ۑ�����
    bool right_button_;        // true : �����ĂȂ�, false : �����Ă��܂� 
    bool left_button_;         // true : �����ĂȂ�, false : �����Ă��܂�

    int break_right_x_;        // �E���̂Ԃ��������Wx
    int break_right_y_;        // �E���̂Ԃ��������Wy

    int break_left_x_;         // �����̂Ԃ��������Wx
    int break_left_y_;         // �����̂Ԃ��������Wy

    int invincible_cnt_;       // ���G���Ԃ̌v��
    bool invincible_;          // true : �Ԃ���, false : ���G���

    bool catch_flag_;          // true : �͂܂��Ă��Ȃ�, false : �͂�ł���
    bool goal_flag_;           // true : �S�[�����Ă��Ȃ�, false : �S�[�����Ă���
    bool extinguish_existence_;// flase : ���݂�����

    int down_cnt_;             // ���̒l��66�ɂȂ�����������]
    int throw_cnt_;            // �����郂�[�V�����̈ێ�
    bool throw_flag_;            // �����郂�[�V�����̈ێ�

    int push_time_jump_;       // 1 = Pressed,2 <= Held
    int push_time_fire_;       // 1 = Pressed,2 <= Held
    int push_time_run_;        // 1 = Pressed,2 <= Held
    int push_time_squat_;      // 1 = Pressed,2 <= Held
};