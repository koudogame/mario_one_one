#include "player.hpp"

Player::Player()
{
    texture_ = NULL;
    pos_x_ = kStartX;
    pos_y_ = kStartY;
}

Player::~Player()
{
}

bool Player::initialize()
{
    texture_ = LoadGraph( "Texture/mario_anime.png" );
    pos_x_ = kStartX;
    pos_y_ = kStartY;

    left_ = 0;
    top_ = 0;
    right_ = 0;
    bottom_ = 0;

    status_ = kMario;

    scroll_cnt_ = 0;               // 右に抜けた分増やしていく

    animation_ = 0;                // 立っているだけの状態
    direction_ = true;             // 初期は右向き

    animation_cnt_ = 0;            // 何もしていないときは動かない
    animation_flag_ = true;        // ジャンプしているとき以外は移動時アニメーション

    old_right_button_ = true;
    old_left_button_ = true;

    right_button_ = true;
    left_button_ = true;

    acceleration_ = 0;
    jumping_ = true;

    return true;
}

void Player::update()
{
    // 右入力
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_RIGHT) == 0 )
    {
        direction_ = true;         // 向きを右向きに変える
        right_button_ = false;     // 押している 


        animation();               // 歩いているアニメーション


        pos_x_ += kSpeed;          // 右への移動


                                   // pos_x_ センターを超えるとき
        if( pos_x_ > kEndLine )
        {
            scroll_cnt_ += kSpeed;
            pos_x_ = kEndLine;
        }
    }
    else
        right_button_ = true;

    // 左入力
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_LEFT) == 0 )
    {
        direction_ = false;        // 向きを左向きに変える
        left_button_ = false;      // 押している


        animation();               // 歩いているアニメーション


        // ポジションゼロより左の時
        if( pos_x_ <= 0 )
        {
            pos_x_ = 0;
        }
        // 左壁以外の時
        else
        {
            pos_x_ -= kSpeed;
        }
    }
    else
        left_button_ = true;

    // 入力が終わったときに比較する
    if( old_left_button_ == false && left_button_ == true ||
        old_right_button_ == false && right_button_ == true )
    {
        animation_ = 0;
        animation_cnt_ = 0;
    }        
    
    // 過去に引き継ぐ
    old_left_button_ = left_button_;
    old_right_button_ = right_button_;

    // ジャンプ入力
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_B) == 0 )
    {
        // ジャンプRECTに切り替え
        // kMario状態の時のみ有効
        animation_ = 4;
        
        // ジャンプ中にアニメーションを動かさないようにする
        animation_flag_ = false;

        // 着地したら再び飛べるようにする
        if( jumping_ == true )
        {
            jumping_ = false;
            acceleration_ = -kJumpPower;
        }
    }

    // ジャンプをした時重力をかける
    if( jumping_ == false )
    {
        acceleration_ += kGravity;

        // マリオを飛ばす
        pos_y_ += acceleration_;
    }
}

void Player::draw()
{
    // マリオのとき
    if( status_ == kMario )
    {
        left_ = animation_ * kSize;
        top_ = kMario;

        right_ = kSize;
        bottom_ = top_ + kSize;
    }
    // else if( status_ == kSuperMario){}を追加する

    if( direction_ == true )
    {
        // 右向きマリオの描画
        DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_,
            texture_, TRUE, FALSE );
    }
    else
    {
        // 左向きマリオの描画
        DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_,
            texture_, TRUE, TRUE );
    }
}

void Player::finalize()
{
    // テクスチャ開放
    DeleteGraph( texture_ );
}

void Player::animation()
{
    // 動いても良いか調べる
    if( animation_flag_ == true )
    {
        animation_cnt_++;

        if( animation_cnt_ >= 5 )
        {
            animation_cnt_ = 0;

            if( animation_ <= 2 )
            {
                animation_++;
            }
            else
            {
                animation_ = 1;
            }
        }
    }

}
