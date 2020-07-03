#include "player.hpp"

Player::~Player()
{
}

bool Player::initialize()
{
    texture_          = LoadGraph( "Texture/mario_anime.png" );
    pos_x_            = kStartX;
    pos_y_            = kStartY;

    // 数値の中のポジション
    total_movement_x_ = 256;
    total_movement_y_ = 832;

    left_             = 0;
    top_              = 0;
    right_            = 0;
    bottom_           = 0;

    status_           = kMario;
    past_status_      = status_;

    scroll_cnt_       = 0;            // 右に抜けた分増やしていく

    gameover_flag_    = true;         // これが立ったら死ぬ

    animation_        = 0;            // 立っているだけの状態
    direction_        = true;         // 初期は右向き

    animation_cnt_    = 0;            // 何もしていないときは動かない
    animation_flag_   = true;         // ジャンプしているとき以外は移動時アニメーション

    old_right_button_ = true;
    old_left_button_  = true;

    right_button_     = true;
    left_button_      = true;

    acceleration_     = 0;
    jumping_          = kJump;

    break_right_x_    = 0;
    break_right_y_    = 0;

    break_left_x_     = 0;
    break_left_y_     = 0;

    invincible_       = true;
    invincible_cnt_   = 0;

    goal_flag_        = true;
    catch_flag_       = true;
    extinguish_existence_ = true;

    down_cnt_         = 0;

    // 始まったときstatus_がkMario以外なら
    if( status_ != kMario )
    {
        pos_y_ -= kSize;
        total_movement_y_ -= kSize;
    }

    return true;
}

bool Player::update()
{
    if( !goal_flag_ ) Ending();
        
    // GameOver判定
    else if( gameover_flag_ )
    {
        // 右入力
        if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_RIGHT) == 0 )
        {
            direction_ = true;         // 向きを右向きに変える
            right_button_ = false;     // 押している(トラッカー)    

            body_[ kRight ][ kShoulder ][ kX ] = (total_movement_x_ + kSize + 1);
            body_[ kRight ][ kShoulder ][ kY ] = (total_movement_y_);

            body_[ kRight ][ kHands ][ kX ] = (total_movement_x_ + kSize + 1);
            // status_がkMarioの時
            if( status_ == kMario )
                body_[ kRight ][ kHands ][ kY ] = (total_movement_y_ + kSize - 1);
            else
                body_[ kRight ][ kHands ][ kY ] = (total_movement_y_ + (kSize * 2) - 1);

            // 当たり判定のないブロックのとき
            if( Collision::sideColl( kRight ) == true )
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
            body_[ kLeft ][ kShoulder ][ kX ] = (total_movement_x_ - 1);
            body_[ kLeft ][ kShoulder ][ kY ] = (total_movement_y_);

            body_[ kLeft ][ kHands ][ kX ] = (total_movement_x_ - 1);

            // 下の位置だけ状態に応じて変更する
            if( status_ == kMario )
                body_[ kLeft ][ kHands ][ kY ] = (total_movement_y_ + kSize - 1);
            else
                body_[ kLeft ][ kHands ][ kY ] = (total_movement_y_ + (kSize * 2) - 1);

            // マリオの左側に衝突するブロックがないとき
            if( Collision::sideColl( kLeft ) == true )
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

            if( jumping_ == kJump )
            {
                jumping_ = kNoJump;
                acceleration_ = -kJumpPower;
            }
        }

        // ジャンプをした時重力をかける
        if( jumping_ == kNoJump )
        {
            acceleration_ += kGravity;

            // マリオを飛ばす
            pos_y_ += acceleration_;
            total_movement_y_ += acceleration_;
        }

        // ２段着地しないようにする魔法の数字
        if( acceleration_ >= 20 )
        {
            acceleration_ = 20;
        }

        // マリオの頭(幅を左右10小さく)
        body_[ kRight ][ kHead ][ kX ] = (total_movement_x_ + (kSize - 10));
        body_[ kRight ][ kHead ][ kY ] = (total_movement_y_ - 1);
        body_[ kLeft ][ kHead ][ kX ] = (total_movement_x_ + 10);
        body_[ kLeft ][ kHead ][ kY ] = (total_movement_y_ - 1);

        // マリオの足元
        body_[ kRight ][ kFoot ][ kX ] = (total_movement_x_ + (kSize - 10));
        body_[ kLeft ][ kFoot ][ kX ] = (total_movement_x_ + 10);

        if( status_ == kMario )
        {
            body_[ kRight ][ kFoot ][ kY ] = (total_movement_y_ + kSize + 1);
            body_[ kLeft ][ kFoot ][ kY ] = (total_movement_y_ + kSize + 1);
        }
        else
        {
            body_[ kRight ][ kFoot ][ kY ] = (total_movement_y_ + (kSize * 2) + 1);
            body_[ kLeft ][ kFoot ][ kY ] = (total_movement_y_ + (kSize * 2) + 1);
        }

        // 上へ飛んでいるときにだけhit()を呼ぶ
        if( acceleration_ < 0 )
        {
            // 右頭にあたるとき
            if( Collision::collision( kRight, kHead ) <= 64 )
            {
                break_right_x_ = (total_movement_x_ / 64) + 1;
                break_right_y_ = total_movement_y_ / 64;
            }

            // 左頭にあたるとき
            if( Collision::collision( kLeft, kHead ) <= 64 )
            {
                break_left_x_ = (total_movement_x_ / 64);
                break_left_y_ = total_movement_y_ / 64;
            }

            if( Collision::collision( kRight, kHead ) <= 64 ||
                Collision::collision( kLeft, kHead ) <= 64 )
            {
                // 頭をぶつけたときの判定
                hit();
            }
        }
        // 上へ飛ぶ加速がなくなったときに下の判定を取り始める
        else
        {
            // 足元の衝突判定
            collision();
        }

        // ゴール
        if( total_movement_x_ >= (kSize * 194) + (kSize / 2) )
        {
            animation_flag_   = true;
            catch_flag_       = false;
            goal_flag_        = false;
            animation_        = 6;
            acceleration_     = 0;
            total_movement_x_ = (kSize * 194) + (kSize / 2);
        }
    }
    // 死んでいるとき
    else
    {
        // 落ちたとき演出無く死亡
        if( pos_y_ > kDeadLine )
        {
            return false;
        }

        // status_がマイナスの時
        // GameOver Action
        acceleration_ += kGravity;

        // マリオを飛ばす
        pos_y_ += acceleration_;
        total_movement_y_ += acceleration_;
    }

    // 無敵時間制限
    if( !invincible_ )
    {
        invincible_cnt_++;

        // 時間が来たら無敵解除
        if( invincible_cnt_ > kInvincible )
        {
            invincible_cnt_ = 0;
            invincible_ = true;
        }
    }

    return true;
}

void Player::draw()
{
    if( extinguish_existence_ )
    {
        break_left_x_ = 0; break_left_y_ = 0;
        break_right_x_ = 0; break_right_y_ = 0;

        if( status_ >= kMario )
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

            if( invincible_ )
                // 右向きマリオの描画
                DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_, texture_, TRUE, !direction_ );
            else
                SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 );
            DrawRectGraph( pos_x_, pos_y_, left_, top_, right_, bottom_, texture_, TRUE, !direction_ );
            SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 );
        }
        else
        {
            if( invincible_ )
                DrawRectGraph( pos_x_, pos_y_, 0, kSize, kSize, kSize, texture_, TRUE, FALSE );
            else
                DrawRectGraph( pos_x_, pos_y_, 0, kSize, kSize, kSize, texture_, TRUE, FALSE );
        }
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
                animation_++;
            else
                animation_ = 1;
        }
    }
}

void Player::collision()
{
    // 足元にあるブロックが乗れるとき
    if( Collision::footColl() == 1 )
    {
        landing();          // 着地処理

        acceleration_ = 0;  // 落下速度

        int block_line = std::round( static_cast<float>(total_movement_y_) / 64 );
        pos_y_ = (block_line - 4) * kSize;
        total_movement_y_ = block_line * kSize;
    }
    // 足元に何もなく浮いているとき
    else if( Collision::footColl() == 2 )
    {
        // 飛べないようにする
        jumping_ = kNoJump;

        // マリオが画面外に行ったとき
        if( pos_y_ > 670 )
        {
            // gameover
            gameover_flag_ = false;
        }
    }
    // 足元にあるブロックが乗れないとき
    else
    {
        if( status_ == kMario )
        {
            // 床より下の時
            if( pos_y_ > kEndLine )
            {
                landing(); // 着地処理

                pos_y_ = kStartY - 1;
                total_movement_y_ = 831;
            }
        }
        else
        {
            // 床より下の時
            if( pos_y_ > kEndLine - 64 )
            {
                landing(); // 着地処理

                pos_y_ = kStartY - 65;
                total_movement_y_ = 763;
            }
        }
    }
}

void Player::landing()
{
    // フラグリセット        
    if( animation_flag_ == false )
    {
        animation_ = 0;
        animation_flag_ = true;
    }
    jumping_ = kJump;
}

void Player::hit()
{
    // 上への加速度を無くす
    acceleration_ = 0;

    int block_line = std::round( static_cast<float>(total_movement_y_) / 64 );

    // プレイヤーの立つ場所を上の辺の高さにする
    pos_y_ = (block_line - 4) * kSize;
    total_movement_y_ = block_line * kSize;
}

void Player::itemCollision()
{
    // 最終進化じゃないとき
    if( status_ < kFireMario )
    {
        status_ += 1;          // マリオ変身

        if( past_status_ == kMario )
        {
            pos_y_ -= kSize;
            total_movement_y_ -= kSize;
        }

        // 変身後の状態を保存
        past_status_ = status_;
    }
}

void Player::enemyCollision()
{

    if( past_status_ == kFireMario )
    {
        status_ -= 2;              // マリオ退化
        invincible_ = false;       // マリオ無敵に変える

        pos_y_ += kSize;
        total_movement_y_ += kSize;
    }
    else if( past_status_ == kSuperMario )
    {
        status_ -= 1;              // マリオ退化
        invincible_ = false;       // マリオ無敵に変える

        pos_y_ += kSize;
        total_movement_y_ += kSize;
    }
    else
    {
        status_ -= 1;              // マリオ退化
        gameover_flag_ = false;
        acceleration_ = -kJumpPower;
    }
    // 変身後の状態を保存
    past_status_ = status_;
}

void Player::enemyStepon()
{
    // ジャンプRECTに切り替え
    animation_ = 4;

    // ジャンプ中にアニメーションを動かさないようにする
    animation_flag_ = false;

    acceleration_ = -kEnemyJump;
}

void Player::Ending()
{        
    // 向き反転までのカウント
    down_cnt_++;

    if( status_ == kMario )
    {
        if( total_movement_y_ < (kSize * 11 + (kSize / 2)) )
        {
            pos_y_ += kDownSpeed;
            total_movement_y_ += kDownSpeed;

            animation_cnt_++;

            if( animation_cnt_ >= 4 )
            {
                animation_cnt_ = 0;

                if( animation_ == 6 )
                    animation_++;
                else
                    animation_--;
            }
        }
        else if( !catch_flag_ && down_cnt_ >= kDownCnt )
        {
            if( !catch_flag_ )
            {
                catch_flag_ = true;
                pos_x_ += kSize;
                total_movement_x_ += kSize;
            }

            direction_ = false;
        }
        else if( down_cnt_ >= kTurnCnt )
        {
            if( total_movement_x_ < (kSize * 201) - (kSize / 2) )
            {
                pos_x_ += 3;
                total_movement_x_ += 3;

                animation();

                if( pos_y_ < kEndLine )
                {
                    acceleration_ += kGravity;
                    pos_y_ += acceleration_;
                    total_movement_y_ += acceleration_;
                }
                else
                {
                    direction_ = true;
                    pos_y_ = kEndLine;
                }
            }
            else
                extinguish_existence_ = false;
        }
    }
    else
        if( total_movement_y_ < (kSize * 10 + (kSize / 2)) )
        {
            pos_y_ += kDownSpeed;
            total_movement_y_ += kDownSpeed;

            animation_cnt_++;

            if( animation_cnt_ >= 4 )
            {
                animation_cnt_ = 0;

                if( animation_ == 6 )
                    animation_++;
                else
                    animation_--;
            }
        }
        else if( !catch_flag_ && down_cnt_ >= kDownCnt )
        {
            if( !catch_flag_ )
            {
                catch_flag_ = true;
                pos_x_ += kSize;
                total_movement_x_ += kSize;
            }

            direction_ = false;
        }
        else if(down_cnt_ >= kTurnCnt)
        {
            if( total_movement_x_ < (kSize * 201) - (kSize / 2) )
            {
                pos_x_ += 3;
                total_movement_x_ += 3;

                animation();

                if( pos_y_ < kEndLine - kSize )
                {
                    acceleration_ += kGravity;
                    pos_y_ += acceleration_;
                    total_movement_y_ += acceleration_;
                }
                else
                {
                    direction_ = true;
                    pos_y_ = kEndLine - kSize;
                }
            }
            else
                extinguish_existence_ = false;
        }
}
