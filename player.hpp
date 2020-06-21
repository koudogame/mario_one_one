#include "field.hpp"
#include "release.hpp"

constexpr int kSize        = 64;
constexpr int kSpeed       = 6;
constexpr int kJumpPower   = 25;
constexpr int kStartX      = 256;
constexpr int kStartY      = 576;
constexpr int kEndLine     = 576;
constexpr int kDeadLine    = 800;
constexpr int kSkyBlue     = 191;
constexpr int kGravity     = 1;

// �}���I�̏�ԕۑ�
enum Status
{
    kMario = 0,
    kSuperMario,
    kFireMario
};

class Player
{
public:
    Player(Field* Field);
    ~Player();
    bool initialize();
    bool update();
    void draw();
    void finalize();

    void animation();          // �}���I�̃A�j���[�V����
    void collision();          // �����̏Փ˔�����s��
    void landing();            // ���n�����Ƃ��̏������s��
    void hit();                // �����Ԃ����Ƃ��̔���

    /*�w�i�̕`��𗬂����l*/
    inline int getScrollCnt() { return scroll_cnt_; }

    /*�}���I�̏�Ԃ�field�ɂ��m�点��*/
    inline int getStatus() { return status_; }

    /*���̓��������Ƃ�*/
    inline int getBreakLeftX() { return break_left_x_; }        /*�����̔z��x*/
    inline int getBreakLeftY() { return break_left_y_; }        /*�����̔z��y*/
    inline int getBreakRightX() { return break_right_x_; }      /*�E���̔z��x*/
    inline int getBreakRightY() { return break_right_y_; }      /*�E���̔z��y*/

private:
    Field* field_;             // Field�̊֐����g����悤�ɂ���

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

    int acceleration_;         // �W�����v�͂�t�^
    bool jumping_;             // true : ��ׂ�, false : ��ׂȂ�

    int break_right_x_;        // �E���̂Ԃ��������Wx
    int break_right_y_;        // �E���̂Ԃ��������Wy

    int break_left_x_;         // �����̂Ԃ��������Wx
    int break_left_y_;         // �����̂Ԃ��������Wy
};