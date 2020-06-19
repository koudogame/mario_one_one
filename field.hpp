#pragma once
#include <vector>
#include <fstream>
#include "block_base.hpp"
#include "both_hands.hpp"
#include "up_and_down.hpp"
#include "release.hpp"

/* NewするClass */
#include "mystery.hpp"

constexpr int kMystery = 48;


class Field
{
public :
    bool initialize(std::fstream& stage);
    void update( int Brx, int Bry, int Blx, int Bly );
    void draw(int ScreenOver);
    void finalize();

    // 体の右側
    int getRightShoulderId( Side side_ );
    int getRightHandId    ( Side side_ );
    // 体の左側
    int getLeftShoulderId ( Side side_ );
    int getLeftHandId     ( Side side_ );
    // 体の上側
    int getRightHeadId    ( UpDown updown_ );
    int getLeftHeadId     ( UpDown updown_ );
    // 体の下側
    int getRightFootId    ( UpDown updown_ );
    int getLeftFootId     ( UpDown updown_ );

private :
    Side side_;                // Side構造体
    UpDown updown_;            // UpDown構造体

    int texture_;              // テクスチャハンドル保存用
    int height_;               // 高さ
    int width_;                // 横幅

    // 数字を設定しなくても増える配列
    std::vector<std::vector<std::vector<BlockBase*>>> field_;
};