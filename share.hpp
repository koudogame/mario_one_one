#pragma once 

static constexpr int kGravity    = 1;        // �d��
static constexpr int kHalfSize   = 32;       // �u���b�N�����̑傫��
static constexpr int kSize       = 64;       // �u���b�N�T�C�Y
static constexpr int kDoubleSize = 128;      // �u���b�N2�{�̑傫��
static constexpr int kQuadruple  = 256;      // �u���b�N4�{�̑傫��

// Rect�Ǘ�
enum Rect
{
    kLeftEdge, kTop, kRightEdge, kBottom, kRect
};


// �}���I�̏��
enum Status
{
    kMario, kSuperMario, kFireMario
};

// �̂̉E�A��
enum RL
{
    kRight, kLeft, kRL
};

//�@�̂̃p�[�c
enum BodyParts
{
    kShoulder, kHands, kHead, kFoot, kBodyParts
};

//�@�̂̃p�[�c��X,Y
enum Position
{
    kX, kY, kPosition
};

// ��я�Ԃ𖾊m�ɂ���
enum JumpFlag
{
    kJump, kNoJump, kNoMove
};