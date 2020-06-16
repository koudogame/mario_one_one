#include "field.hpp"
#include "release.hpp"

constexpr int kSize        = 64;
constexpr int kSpeed       = 6;
constexpr int kJumpPower   = 25;
constexpr int kStartX      = 256;
constexpr int kStartY      = 576;
constexpr int kEndLine     = 576;
constexpr float kGravity   = 0.98F;

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
    Player();
    ~Player();
    bool initialize();
    void update();
    void draw();
    void finalize();

    void animation();
    
    /*�w�i�̕`��𗬂����l*/
    inline int getScrollCnt() { return scroll_cnt_; }                

private:
    int texture_;              // �e�N�X�`���n���h��

    int pos_x_;                // ���Wx
    int pos_y_;                // ���Wy 

    int left_;                 // SrcX
    int top_;                  // SrcY

    int right_;                // Width
    int bottom_;               // Height

    int status_;               // �}���I�̏��

    int scroll_cnt_;           // �������}���I���������Ƃ��ɃX�N���[��

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
};