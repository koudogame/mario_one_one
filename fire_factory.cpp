#include "fire_factory.hpp"

void FireFactory::initialize( int PosX, int PosY, int Direction)
{
    // 投げられた時のマリオの座標をスタート位置とする
    fire_pos_x_ = PosX + (kSize / 2);
    fire_pos_y_ = PosY - (kSize * 4) + (kSize / 2);

    // マリオの向きの受け渡し
    direction_ = Direction;

    // sideTouch
    side_touch_ = true;

    // アニメ用変数初期化
    animation_ = 0;
    animation_cnt_ = 0;
}

void FireFactory::update()
{
    animation();            // ファイアボールアニメーション
    fire_pos_x_ += kSpeed * direction_;

    // 下の部分の登録(Collision)
    // 右足、左足の登録
    body_[ kRight ][ kFoot ][ kX ] = fire_pos_x_ + ((kSize / 2) - 5);
    body_[ kRight ][ kFoot ][ kY ] = fire_pos_y_ + ((kSize / 2) + 1) + (kSize * 4);

    body_[ kLeft ][ kFoot ][ kX ] = fire_pos_x_ + 5;
    body_[ kLeft ][ kFoot ][ kY ] = fire_pos_y_ + ((kSize / 2) + 1) + (kSize * 4);

    // 足場があるとき
    if( Collision::footColl() == 1 )
    {
        jumping_ = kNoMove;

        int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;
        fire_pos_y_ = ((block_line - 4) * kSize) + kSize - 1;

        if( block_line >= 14 )
            fire_pos_y_ = kGround;

        acceleration_ = 0;  // 落下速度
        acceleration_ = -kJumpPower;
    }
    // 宙に浮いているとき
    else if( Collision::footColl() == 2 )
    {
        jumping_ = kNoJump;

        if( fire_pos_y_ > 670 )
            jumping_ = kNoMove;

        // 宙に浮いているとき落下
        if( jumping_ == kNoJump )
        {
            acceleration_ += kGravity;
            fire_pos_y_ += acceleration_;
        }
    }

    // 右サイドの登録
    body_[ kRight ][ kShoulder ][ kX ] = fire_pos_x_ + (kSize / 2) + 1;
    body_[ kRight ][ kShoulder ][ kY ] = (fire_pos_y_ + 4) + (kSize * 4);
    body_[ kRight ][ kHands ][ kX ] = fire_pos_x_ + (kSize / 2) + 1;
    body_[ kRight ][ kHands ][ kY ] = (fire_pos_y_ - 4) + (kSize * 4);

    // 当たり判定があるとき
    if( Collision::sideColl( kRight ) == false )
        // 当たり判定処理
        side_touch_ = false;

    // 左サイドの登録
    body_[ kLeft ][ kShoulder ][ kX ] = fire_pos_x_ - 1;
    body_[ kLeft ][ kShoulder ][ kY ] = fire_pos_y_ + 4 + (kSize * 4);
    body_[ kLeft ][ kHands ][ kX ] = fire_pos_x_ - 1;
    body_[ kLeft ][ kHands ][ kY ] = fire_pos_y_ - 4 + (kSize * 4);

    // 当たり判定があるとき
    if( Collision::sideColl( kLeft ) == false )
        // 当たり判定処理
        side_touch_ = false;
}

void FireFactory::draw( int Texture, const int ScreenOver )
{
    texture_ = Texture;

    int top    = kSize * 6;
    int bottom = kSize / 2;

    int left   = (animation_ * (kSize / 2));
    int right  = kSize / 2;

    int x = fire_pos_x_ - ScreenOver;

    DrawRectGraph( x, fire_pos_y_,
        left, top, right, bottom, texture_, TRUE, FALSE );
}

bool FireFactory::getCheckScreen( const int ScreenOver )
{        
    // FireBallと、画面の大きさ
    int screen_left   = ScreenOver;
    int screen_right  = ScreenOver + kScreenXSize;

    int screen_top    = 0;
    int screen_bottom = kScreenYSize;

    int fire_left     = fire_pos_x_;
    int fire_right    = fire_pos_x_ + (kSize / 2);

    int fire_top      = fire_pos_y_;
    int fire_bottom   = fire_pos_y_ + (kSize / 2);

    // 画面内にいるとき
    if( (screen_right > fire_left) && (fire_right > screen_left)
        && (screen_bottom > fire_top) && (fire_bottom > screen_top) )
    {
        return true;
    }
    else
    // 画面外
    return false;
}

void FireFactory::animation()
{
    animation_cnt_++;

    if( animation_cnt_ >= kAnime )
    {
        animation_cnt_ = 0;
        animation_++;

        if( animation_ >= 4 )
            animation_ = 0;
    }
}
