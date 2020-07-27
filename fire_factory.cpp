#include "fire_factory.hpp"

void FireFactory::initialize( int PosX, int PosY, int Direction)
{
    // 投げられた時のマリオの座標をスタート位置とする
    fire_pos_x_    = PosX + kHalfSize;
    fire_pos_y_    = PosY + kHalfSize - kQuadruple;

    // マリオの向きの受け渡し
    direction_     = Direction;

    // sideTouch
    side_touch_    = true;

    // アニメ用変数初期化
    animation_     = 0;
    animation_cnt_ = 0;

    explode_cnt_   = 0;
    explode_flag_  = true;
}

void FireFactory::update()
{
    // どこかにぶつかるまで
    if( side_touch_ )
    {
        // ファイアアニメーション
        animation();            
        
        // 常に横移動
        fire_pos_x_ += kSpeed * direction_;

        // 右サイドの登録
        body_[ kRight ][ kShoulder ][ kX ] = fire_pos_x_ + kHalfSize + 1;
        body_[ kRight ][ kShoulder ][ kY ] = (fire_pos_y_ + kDisplace) + kQuadruple;
        body_[ kRight ][ kHands ][ kX ] = fire_pos_x_ + kHalfSize + 1;
        body_[ kRight ][ kHands ][ kY ] = (fire_pos_y_ - kDisplace) + kQuadruple;

        // 当たり判定があるとき
        if( !Collision::sideColl( kRight ))
            // 当たり判定処理
            side_touch_ = false;

        // 左サイドの登録
        body_[ kLeft ][ kShoulder ][ kX ] = fire_pos_x_ - 1;
        body_[ kLeft ][ kShoulder ][ kY ] = fire_pos_y_ + kQuadruple + kDisplace;
        body_[ kLeft ][ kHands ][ kX ] = fire_pos_x_ - 1;
        body_[ kLeft ][ kHands ][ kY ] = fire_pos_y_ + kQuadruple - kDisplace;

        // 当たり判定があるとき
        if( !Collision::sideColl( kLeft ))
            // 当たり判定処理
            side_touch_ = false;


        // 下の部分の登録(Collision)
        // 右足、左足の登録
        body_[ kRight ][ kFoot ][ kX ] = fire_pos_x_ + (kHalfSize - kDisplace);
        body_[ kRight ][ kFoot ][ kY ] = fire_pos_y_ + (kHalfSize + 1) + kQuadruple;

        body_[ kLeft ][ kFoot ][ kX ] = fire_pos_x_ + kDisplace;
        body_[ kLeft ][ kFoot ][ kY ] = fire_pos_y_ + (kHalfSize + 1) + kQuadruple;

        // 足場があるとき
        if( Collision::fireColl() == 3 )
        {
            jumping_ = kNoMove;

            int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;
            fire_pos_y_ = ((block_line - kControl) * kSize) - kSize;

            if( block_line >= kGroundArray )
                fire_pos_y_ = kGround;

            acceleration_ = 0;  // 落下速度
            acceleration_ = (-kJumpPower / 2);
        }
        else if( Collision::fireColl() == 1 )
        {
            jumping_ = kNoMove;

            int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;
            fire_pos_y_ = ((block_line - kControl) * kSize) - kSize;

            if( block_line >= kGroundArray )
                fire_pos_y_ = kGround;

            acceleration_ = 0;  // 落下速度
            acceleration_ = -kJumpPower;
        }
        // 宙に浮いているとき
        else if( Collision::fireColl() == 2 )
        {
            jumping_ = kNoJump;

            // 宙に浮いているとき落下
            if( jumping_ == kNoJump )
            {
                acceleration_ += kGravity;
                fire_pos_y_ += acceleration_;
            }
        }
    }
    else
        // ぶつかったとき
        burnAnimation();
}

void FireFactory::draw( int Texture, const int ScreenOver )
{
    texture_ = Texture;

    int top    = kSextuple;
    int bottom = kHalfSize;

    int left   = (animation_ * kHalfSize);
    int right  = kHalfSize;

    int x = fire_pos_x_ - ScreenOver;

    if(side_touch_)
    DrawRectGraph( x, fire_pos_y_,
        left, top, right, bottom, texture_, TRUE, FALSE );    
    DrawRectGraph( x, fire_pos_y_,
        explosion_[ kLeftEdge ], explosion_[ kTop ], explosion_[ kRightEdge ], explosion_[ kBottom ],
        texture_, TRUE, FALSE );
}

// 画面内にいるか確認する関数
bool FireFactory::getCheckScreen( const int ScreenOver )
{        
    // FireBallと、画面の大きさ
    int screen_left   = ScreenOver;
    int screen_right  = ScreenOver + kScreenXSize;

    int screen_top    = 0;
    int screen_bottom = kScreenYSize;

    int fire_left     = fire_pos_x_;
    int fire_right    = fire_pos_x_ + kHalfSize;

    int fire_top      = fire_pos_y_;
    int fire_bottom   = fire_pos_y_ + kHalfSize;

    // 画面内にいるとき
    if( (screen_right > fire_left) && (fire_right > screen_left)
        && (screen_bottom > fire_top) && (fire_bottom > screen_top) )
        return true;
    else
    // 画面外
    return false;
}

// ファイアボールのアニメーション制御する関数
void FireFactory::animation()
{
    animation_cnt_++;

    if( animation_cnt_ >= kAnime )
    {
        animation_cnt_ = 0;
        animation_++;

        if( animation_ >= kLimit )
            animation_ = 0;
    }
}

// どこかしらと当たったとき爆発を起こす関数
void FireFactory::burnAnimation()
{
    explode_cnt_++;

    if( explode_cnt_ <= kSmall )
    {
        // RECTの値を変更（小爆発）
        explosion_[ kLeftEdge ]   = 0;
        explosion_[ kTop ]        = kSeptuple;
        explosion_[ kRightEdge ]  = kSize;
        explosion_[ kBottom ]     = kSize;
    }
    else if( explode_cnt_ <= kBic )
        explosion_[ kLeftEdge ] = kSize;
    else
        // 一通りしたら消す(erase)
        explode_flag_ = false;
}

void FireFactory::setFire( bool Fire )
{
    if( !Fire )
    {
        side_touch_ = false;

        if(explode_flag_)
        burnAnimation();
    }
}
