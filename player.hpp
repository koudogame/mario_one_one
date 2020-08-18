#include "collision.hpp"
#include "namespace.hpp"

class Player :
    public Collision
{
public:
    const int kSliding    = 5;   // �X���C�f�B���O�A�j�� 
    const int kSpeed      = 6;   // �����Ă���Ƃ��̑��x
    const int kDownSpeed  = 6;   // �S�[�������Ƃ�������X�s�[�h
    const int kAnimeMove  = 8;   // �A�j���[�V�����p
    const int kEnemyJump  = 8;   // �G�𓥂񂾎��̃W�����v��
    const int kDashSpeed  = 10;  // �_�b�V�����Ă���Ƃ��̑��x
    const int kStopper    = 16;  // �A�˖h�~�X�g�b�p�[
    const int kJumpPower  = 24;  // �W�����v�{�^�����̃W�����v��
    const int kDownCnt    = 66;  // �͂�ł���̑҂�����
    const int kTurnCnt    = 90;  // �������]�����邽�߂̎���
    const int kInvincible = 180; // ���G��������
    const int kSkyBlue    = 191; // �w�i�̉����Ȃ������}�b�v�`�b�vID
    const int kGoalPost   = 194; // �S�[���|�X�g
    const int kEntrance   = 201; // ���̓����
    const int kStartX     = 256; // �������WX
    const int kStartY     = 576; // �������WY
    const int kEndLine    = 576; // ��ʂ̒��S
    const int kDeadLine   = 800; // ���̐��l��艺�͎���

    PlayerData getData();

    Player( Field* field ) : Collision( field ) {};
    bool initialize();
    bool update(bool);
    void draw();
    void finalize();

    void animation();            // �}���I�̃A�j���[�V����
    void collision();            // �����̏Փ˔�����s��
    void landing();              // ���n�����Ƃ��̏������s��
    void hit();                  // �����Ԃ����Ƃ��̔���
    void itemCollision();        // �A�C�e���ɓ��������Ƃ�
    void enemyCollision();       // �Ԃ������Ƃ��̏���
    void enemyStepon();          // ���݂����Ƃ��̏���      
    void ending();               // �G���f�B���O����
    void rightCheck();           // �̂̉E����o�^���ă`�F�b�N����֐�
    void leftCheck();            // �̂̍�����o�^���ă`�F�b�N����֐�

    inline bool getInvincibleTime() { return invincible_time_; }

    // �����ɉ����ēn��
    inline int getDirection() 
    {
        if( direction_ ) return 1;
        else return -1;
    }
    
private:
    PlayerData data_;               // �f�[�^�󂯓n���p�ϐ�

    Rect<int> rect_;                // Rect�Ăяo��
    Position<int> position_;        // Position�Ăяo��
    Position<int> total_move_;      // Position�Ăяo��
    Position<int> break_right_;     // ���̉E�̍��W
    Position<int> break_left_;      // ���̍��̍��W
                                    
    int texture_;                   // �e�N�X�`���n���h��
    int past_status_;               // �}���I�̉ߋ��̏��
                                                                                                            
    int animation_;                 // �����Ă���Ƃ��̐؂���͈�
    bool direction_;                // true : �E����, false : ������
                                    
    int animation_cnt_;             // ���������߂̃A�j���[�V������������ 
    bool animation_flag_;           // true : ����, false : �����Ȃ�
                                    
    bool old_right_button_;         // true : �����ĂȂ�, false : �����Ă��܂�
    bool old_left_button_;          // true : �����ĂȂ�, false : �����Ă��܂�
    bool old_down_button_;          // true : �����ĂȂ�, false : �����Ă��܂�
                                    
    bool right_button_;             // true : �����ĂȂ�, false : �����Ă��܂� 
    bool left_button_;              // true : �����ĂȂ�, false : �����Ă��܂�
                                    
    int invincible_cnt_;            // ���G���Ԃ̌v��
    bool invincible_time_;          // ���G���������鎞��
                                    
    bool catch_flag_;               // true : �͂܂��Ă��Ȃ�, false : �͂�ł���
                                    
    int down_cnt_;                  // ���̒l��66�ɂȂ�����������]
    int throw_cnt_;                 // �����郂�[�V�����̈ێ�
    bool throw_flag_;               // �����郂�[�V�����̈ێ�
                                    
    int push_time_jump_;            // 1 = Pressed,2 <= Held
    int push_time_fire_;            // 1 = Pressed,2 <= Held
    int push_time_run_;             // 1 = Pressed,2 <= Held
    int timekeep_squat_;            // 1 = Pressed,2 <= Held
                                    
    int speed_;                     // �����x
    int speed_up_;                  // ���t���[���łP��������s��
    int speed_down_;                // ���t���[���łP�񌸑����s��
    bool sliding_;                  // true : �����Ă���, false : �����Ă��Ȃ�
                                    
    void squat();                   // ���Ⴊ�ޓ�����s���֐�
    void fireMove();                // �t�@�C�A�{�[���𓊂��铮��
    void defaultSize( int Status ); // ������rect_�𒲐�����֐�

    void rightPush();               // �E�����������̏���
    void leftPush();                // �������������̏���
};