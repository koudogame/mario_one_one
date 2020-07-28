#pragma once 
#include <vector>
#include <DxLib.h>
#include <fstream>
#include <crtdbg.h>
#include <windows.h>
#include "rect.hpp"

/*�萔�Q*/
constexpr int kGravity     = 1;              // �d��
constexpr int kControl     = 4;              // �z��`�撲���p
constexpr int kDisplace    = 4;              // �����A�O����
constexpr int kGather      = 10;             // �񂹂Ă����(position)
constexpr int kGroundArray = 13;             // �n�ʂɒl����z��ԍ�
constexpr int kLength      = 16;             // �z��̉��̒���
constexpr int kMoveStart   = 20;             // �G�l�~�[�����o��
constexpr int kHalfSize    = 32;             // �u���b�N�����̑傫��
constexpr int kSize        = 64;             // �u���b�N�T�C�Y
constexpr int kDoubleSize  = kSize * 2;      // �u���b�N2�{�̑傫��
constexpr int kTripleSize  = kSize * 3;      // �u���b�N3�{�̑傫��
constexpr int kQuadruple   = kSize * 4;      // �u���b�N4�{�̑傫��
constexpr int Quintuple    = kSize * 5;      // �u���b�N5�{�̑傫��
constexpr int kSextuple    = kSize * 6;      // �u���b�N6�{�̑傫��
constexpr int kSeptuple    = kSize * 7;      // �u���b�N7�{�̑傫��
constexpr int kOctuple     = kSize * 8;      // �u���b�N8�{�̑傫��
constexpr int kDecuple     = kSize * 10;     // �u���b�N10�{�̑傫��
constexpr int kFallOut     = 670;            // �n�ʂ̌��E

/*�u���b�NID*/
constexpr int kUsedBlock   = 16;       // �@���ꂽID
constexpr int kBrick       = 19;       // �����K�u���b�N
constexpr int kMystery     = 48;       // �͂Ăȃu���b�N

/*�G�l�~�[ID*/
constexpr int kKuribo      = 0;        // �N���{�[ID
constexpr int kTurtle      = 36;       // �m�R�m�RID
constexpr int kShell       = 113;      // �������ID 

/*�A�C�e��ID*/
constexpr int kMashroom    = 0;        // �L�m�RID
constexpr int kFlag        = 3;        // ��ID
constexpr int kFlower      = 16;       // �t�����[ID
constexpr int kGoal        = 19;       // �S�[��ID
constexpr int kCoin        = 80;       // �R�C��ID

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