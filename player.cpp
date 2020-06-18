#include "player.hpp"

Player::Player( Field* field )
{
    field_ = field;
    texture_ = NULL;
    
    // 目に見えるポジション
    pos_x_ = kStartX;
    pos_y_ = kStartY;

    // 数値の中のポジション
    total_movement_x_ = 256;
    total_movement_y_ = 832;
}

Player::~Player()
{
}

bool Player::initialize()
{
    texture_ = LoadGraph( "Texture/mario_anime.png" );
    pos_x_ = kStartX;
    pos_y_ = kStartY;

    // 数値の中のポジション
    total_movement_x_ = 256;
    total_movement_y_ = 832;

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

    // 始まったときstatus_がkMario以外なら
    if( status_ != kMario )
    {
        pos_y_ -= kSize;
        total_movement_y_ -= kSize;
    }

    return true;
}

void Player::update()
{
    // 右入力
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_RIGHT) == 0 )
    {
        direction_ = true;         // 向きを右向きに変える
        right_button_ = false;     // 押している(トラッカー)            
        

        // 上と両サイドは変更なし
        side_.right_shoulder_x = total_movement_x_ + kSize + 1;
        side_.right_hand_x = total_movement_x_ + kSize + 1;
        side_.right_shoulder_y = total_movement_y_;

        // status_がkMarioの時
        if( status_ == kMario )
         side_.right_hand_y = total_movement_y_ + kSize;
        else
         side_.right_hand_y = total_movement_y_ + (kSize * 2);


        // 当たり判定のないブロックのとき
        if( field_->getRightShoulderId( side_ ) > 64 &&
            field_->getRightHandId( side_ ) > 64 )
        {

            // 右への移動
            pos_x_ += kSpeed;
            total_movement_x_ += kSpeed;

            // pos_x_ センターを超えるとき
            if( pos_x_ > kEndLine )
            {
                scroll_cnt_ += kSpeed;
                pos_x_ = kEndLine;
            }
        }

        // デバッグ用変数
        int shoulder = field_->getRightShoulderId( side_ );
        int hand = field_->getRightHandId( side_ );

        animation();               // 歩いているアニメーション
    }
    else
        right_button_ = true;

    // 左入力
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_LEFT) == 0 )
    {
        direction_ = false;        // 向きを左向きに変える
        left_button_ = false;      // 押している

        // 上と両サイドは変更なし
        side_.left_shoulder_x = total_movement_x_ - 1;
        side_.left_hand_x     = total_movement_x_ - 1;
        side_.left_shoulder_y = total_movement_y_;

        if( status_ == kMario )
            side_.left_hand_y = total_movement_y_ + kSize;
        else
            side_.left_hand_y = total_movement_y_ + (kSize * 2);


        // マリオの右側に衝突するブロックがないとき
        if( field_->getLeftShoulderId( side_ ) > 64 &&
            field_->getLeftHandId( side_ ) > 64 )
        {
            // ポジションゼロより左の時
            if( pos_x_ <= 0 )
            {
                pos_x_ = 0;
            }
            // 左壁以外の時
            else
            {
                pos_x_ -= kSpeed;
                total_movement_x_ -= kSpeed;
            }
        }

        animation();               // 歩いているアニメーション
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
        total_movement_y_ = pos_y_;
    }

    ////////////////////////////////////////////////////
    // デバッグ用 足元判定が取れるまでkEndLineを設定する
    if( status_ == kMario )
    {
        if( pos_y_ > kEndLine )
        {
            pos_y_ = kStartY - 1;
            total_movement_y_ = 831;

            // 着地        
            if( animation_flag_ == false )
            {
                animation_ = 0;
                animation_flag_ = true;
            }
            jumping_ = true;
        }
    }
    else
    {
        if( pos_y_ > kEndLine - 64)
        {
            pos_y_ = kStartY - 65;
            total_movement_y_ = 763;

            // 着地        
            if( animation_flag_ == false )
            {
                animation_ = 0;
                animation_flag_ = true;
            }
            jumping_ = true;
        }
    }
    ////////////////////////////////////////////////////

}

void Player::draw()
{   
    // 状態は変わってもwidthは変わらない
     left_ = animation_ * kSize;
    right_ = kSize;

    // マリオのとき
    if( status_ == kMario )
    {
        top_ = kMario * kSize;
        bottom_ = top_ + kSize;
    }
    // スーパーマリオのとき
    else if( status_ == kSuperMario )
    {
        top_ = kSize * 4;
        bottom_ = kSize * 2;
    }
    // ファイアマリオのとき
    else if( status_ == kFireMario )
    {
        top_ = kSize * 8;
        bottom_ = kSize * 2;
    }

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
