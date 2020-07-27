#pragma once 

static constexpr int kGravity    = 1;        // 重力
static constexpr int kHalfSize   = 32;       // ブロック半分の大きさ
static constexpr int kSize       = 64;       // ブロックサイズ
static constexpr int kDoubleSize = 128;      // ブロック2倍の大きさ
static constexpr int kQuadruple  = 256;      // ブロック4倍の大きさ

// Rect管理
enum Rect
{
    kLeftEdge, kTop, kRightEdge, kBottom, kRect
};


// マリオの状態
enum Status
{
    kMario, kSuperMario, kFireMario
};

// 体の右、左
enum RL
{
    kRight, kLeft, kRL
};

//　体のパーツ
enum BodyParts
{
    kShoulder, kHands, kHead, kFoot, kBodyParts
};

//　体のパーツのX,Y
enum Position
{
    kX, kY, kPosition
};

// 飛び状態を明確にする
enum JumpFlag
{
    kJump, kNoJump, kNoMove
};