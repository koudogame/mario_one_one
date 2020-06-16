#include "field.hpp"
#include "release.hpp"

static constexpr int kSize = 64;
constexpr int kStartX = 256;
constexpr int kStartY = 576;
constexpr int kEndLine = 576;

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

private:
    int texture_;           // �e�N�X�`���n���h��

    int pos_x_;             // ���Wx
    int pos_y_;             // ���Wy 

    int left_;                 // SrcX
    int top_;                 // SrcY

    int right_;               // Width
    int bottom_;           // Height

    int status_;            // �}���I�̏��

    int animation_;       // �����Ă���Ƃ��̐؂���͈�
    bool direction_;       // true : �E����, false : ������

    const int id_ = 0;    // ControllerId
};