#pragma once 
#include <vector>
#include <DxLib.h>
#include <fstream>
#include <crtdbg.h>
#include <windows.h>
#include "rect.hpp"

/*定数群*/
constexpr int kGravity     = 1;              // 重力
constexpr int kControl     = 4;              // 配列描画調整用
constexpr int kDisplace    = 4;              // 内側、外側寄せ
constexpr int kGather      = 10;             // 寄せている量(position)
constexpr int kGroundArray = 13;             // 地面に値する配列番号
constexpr int kLength      = 16;             // 配列の横の長さ
constexpr int kMoveStart   = 20;             // エネミー動き出し
constexpr int kHalfSize    = 32;             // ブロック半分の大きさ
constexpr int kSize        = 64;             // ブロックサイズ
constexpr int kDoubleSize  = kSize * 2;      // ブロック2倍の大きさ
constexpr int kTripleSize  = kSize * 3;      // ブロック3倍の大きさ
constexpr int kQuadruple   = kSize * 4;      // ブロック4倍の大きさ
constexpr int Quintuple    = kSize * 5;      // ブロック5倍の大きさ
constexpr int kSextuple    = kSize * 6;      // ブロック6倍の大きさ
constexpr int kSeptuple    = kSize * 7;      // ブロック7倍の大きさ
constexpr int kOctuple     = kSize * 8;      // ブロック8倍の大きさ
constexpr int kDecuple     = kSize * 10;     // ブロック10倍の大きさ
constexpr int kFallOut     = 670;            // 地面の限界

/*ブロックID*/
constexpr int kUsedBlock   = 16;       // 叩かれたID
constexpr int kBrick       = 19;       // レンガブロック
constexpr int kMystery     = 48;       // はてなブロック

/*エネミーID*/
constexpr int kKuribo      = 0;        // クリボーID
constexpr int kTurtle      = 36;       // ノコノコID
constexpr int kShell       = 113;      // こうらのID 

/*アイテムID*/
constexpr int kMashroom    = 0;        // キノコID
constexpr int kFlag        = 3;        // 旗ID
constexpr int kFlower      = 16;       // フラワーID
constexpr int kGoal        = 19;       // ゴールID
constexpr int kCoin        = 80;       // コインID

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