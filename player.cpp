#include "player.hpp"

bool Player::initialize()
{
    texture_          = LoadGraph( "Texture/mario_anime.png" );
    position_.x       = kStartX;
    position_.y       = kStartY;
  
    rect_.top         = 0;
    rect_.bottom      = kSize;

    // 数値の中のポジション
    total_move_.x = kStartX;
    total_move_.y = 832;

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

    invincible_       = true;
    invincible_time_  = true;
    invincible_cnt_   = 0;

    goal_flag_        = true;
    catch_flag_       = true;
    extinguish_existence_ = true;

    throw_cnt_ = 0;
    throw_flag_ = true;

    down_cnt_         = 0;

    push_time_jump_ = 0;
    push_time_fire_ = 0;
    push_time_run_  = 0;
    push_time_squat_= 0;

    // 始まったときstatus_がkMario以外なら
    if( status_ != kMario )
    {
        position_.y -= kSize;
        total_move_.y -= kSize;
    }

    return true;
}

bool Player::update(bool TimeLimit)
{
    if( !goal_flag_ ) ending();
    else if( gameover_flag_ )
    {
        if( invincible_time_ )
        {
            // ダッシュボタン判定
            if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4) == 0 || CheckHitKey( KEY_INPUT_B ) == 1 )
                push_time_run_++;
            else
                push_time_run_ = 0;

            if( left_button_ )
            {
                // 右入力
                if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_RIGHT) == 0 || CheckHitKey( KEY_INPUT_D ) == 1 )
                {
                    direction_ = true;         // 向きを右向きに変える
                    right_button_ = false;     // 押している(トラッカー) 

                    rightCheck();              // 体の右側を確認する

                    animation();               // 歩いているアニメーション
                }
                else
                    right_button_ = true;
            }

            if( right_button_ )
            {
                // 左入力
                if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_LEFT) == 0 || CheckHitKey( KEY_INPUT_A ) == 1 )
                {
                    direction_ = false;        // 向きを左向きに変える
                    left_button_ = false;      // 押している

                    leftCheck();

                    animation();               // 歩いているアニメーション
                }
                else
                    left_button_ = true;
            }
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
            if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_B) == 0 || CheckHitKey( KEY_INPUT_SPACE ) == 1 )
                push_time_jump_++;
            else
                push_time_jump_ = 0;

            // 初回限定
            if( push_time_jump_ == 1 )
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
                position_.y += acceleration_;
                total_move_.y += acceleration_;
            }

            // 加速度上限
            if( acceleration_ >= 20 )
            {
                acceleration_ = 20;
            }

            // マリオの頭(幅を左右10小さく)
            body_[ kRight ][ kHead ][ kX ] = (total_move_.x + (kSize - kGather));
            body_[ kRight ][ kHead ][ kY ] = (total_move_.y - 1);
            body_[ kLeft ][ kHead ][ kX ] = (total_move_.x + kGather);
            body_[ kLeft ][ kHead ][ kY ] = (total_move_.y - 1);

            // マリオの足元
            body_[ kRight ][ kFoot ][ kX ] = (total_move_.x + (kSize - kGather));
            body_[ kLeft ][ kFoot ][ kX ] = (total_move_.x + kGather);

            // マリオの時
            if( status_ == kMario )
            {
                body_[ kRight ][ kFoot ][ kY ] = (total_move_.y + kSize + 1);
                body_[ kLeft ][ kFoot ][ kY ] = (total_move_.y + kSize + 1);
            }
            // マリオ以外の時
            else
            {
                body_[ kRight ][ kFoot ][ kY ] = (total_move_.y + kDoubleSize + 1);
                body_[ kLeft ][ kFoot ][ kY ] = (total_move_.y + kDoubleSize + 1);
            }

            // 上へ飛んでいるときにだけhit()を呼ぶ
            if( acceleration_ < 0 )
            {
                // 右頭にあたるとき
                if( Collision::collision( kRight, kHead ) <= kSize )
                {
                    break_right_.x = (total_move_.x / kSize) + 1;
                    break_right_.y = total_move_.y / kSize;
                }

                // 左頭にあたるとき
                if( Collision::collision( kLeft, kHead ) <= kSize )
                {
                    break_left_.x = (total_move_.x / kSize);
                    break_left_.y = total_move_.y / kSize;
                }

                // 頭の上にあるブロックを調べる
                if( Collision::collision( kRight, kHead ) <= kSize ||
                    Collision::collision( kLeft, kHead ) <= kSize )
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
            if( total_move_.x >= (kSize * kGoalPost) + kHalfSize )
            {
                animation_flag_ = true;
                catch_flag_ = false;
                goal_flag_ = false;
                animation_ = 6;
                acceleration_ = 0;
                total_move_.x = (kSize * kGoalPost) + kHalfSize;
            }

            // 時間制限による死亡
            if( !TimeLimit )
            {
                gameover_flag_ = false;
                acceleration_ = -kJumpPower;
                status_ = -1;
            }
        }

        // 無敵時間制限
        if( !invincible_ )
        {
            invincible_cnt_++;

            // ９回拡縮したら解放
            if( invincible_cnt_ > kAnimeMove * kAnimeMove )
                invincible_time_ = true;

            // 時間が来たら無敵解除
            if( invincible_cnt_ > kInvincible )
            {
                invincible_cnt_ = 0;
                invincible_ = true;
            }
        }
    }
    // 死んでいるとき
    else
    {
        // 落ちたとき演出無く死亡
        if( position_.y > kDeadLine )
            return false;

        // status_がマイナスの時
        // GameOver Action
        acceleration_ += kGravity;

        // マリオを飛ばす
        position_.y += acceleration_;
        total_move_.y += acceleration_;
    }

    return true;
}

void Player::draw()
{
    // ゴール前
    if( extinguish_existence_ )
    {
        // 頭の初期化
        break_left_.x = 0; break_left_.y = 0;
        break_right_.x = 0; break_right_.y = 0;

        // 共通範囲
        rect_.left = animation_ * kSize;
        rect_.right = kSize;

        // やられるとき
        if( status_ == -1 )
        {
            rect_.left = 0;
            rect_.top = kSize;
            rect_.right = kSize;
            rect_.bottom = kSize;
        }
        // ファイアマリオ
        else if( status_ == kFireMario )
            fireMove(); // 投げる動き

                // gameclearの時
        if( status_ == kFireMario && !goal_flag_ )
            rect_.top = kOctuple;

        // 無敵状態(半透明)
        if( !invincible_ && status_ != -1 )
        {
            // サイズ変換
            SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 );

            // 大きい、小さいを繰り返す
            int n = invincible_cnt_ / kAnimeMove;
            int m = invincible_cnt_ % kAnimeMove;

            // 8回行うまで繰り返す
            if( invincible_cnt_ <= kAnimeMove * kAnimeMove )
            {
                // 余り０で偶数の時
                if( m == 0 && n % 2 == 0 )
                {
                    // Rectを切り替える
                    rect_.top = 0;
                    rect_.bottom = kSize;

                    // 高さを揃える
                    position_.y += kSize;
                    total_move_.y += kSize;
                }
                // 余り０で奇数の時
                else if( m == 0 && n % 2 == 1 )
                {
                    // Rectを切り替える
                    rect_.top = kQuadruple;
                    rect_.bottom = kDoubleSize;

                    // 高さを揃える
                    position_.y -= kSize;
                    total_move_.y -= kSize;
                }
            }
        }

        // 通常描画
        DrawRectGraph( position_.x, position_.y,
            rect_.left, rect_.top, rect_.right, rect_.bottom,
            texture_, TRUE, !direction_ );

        // 状態を戻す
        SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 );
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

        if( animation_cnt_ >= 4 )
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

        int block_line = static_cast<int>(std::round( static_cast<float>(total_move_.y) / kSize ));
        position_.y = (block_line - kControl) * kSize;
        total_move_.y = block_line * kSize;
    }
    // 足元に何もなく浮いているとき
    else if( Collision::footColl() == 2 )
    {
        // 飛べないようにする
        jumping_ = kNoJump;

        // マリオが画面外に行ったとき
        if( position_.y > kFallOut )
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
            if( position_.y > kEndLine )
            {
                landing(); // 着地処理

                position_.y = kStartY - 1;
                total_move_.y = 831;
            }
        }
        else
        {
            // 床より下の時
            if( position_.y > kEndLine - kSize )
            {
                landing(); // 着地処理

                position_.y = kStartY - kSize - 1;
                total_move_.y = 763;
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

    int block_line = static_cast<int>(std::round( static_cast<float>(total_move_.y) / kSize ));

    // プレイヤーの立つ場所を上の辺の高さにする
    position_.y = (block_line - kControl) * kSize;
    total_move_.y = block_line * kSize;
}

void Player::itemCollision()
{
    // 最終進化じゃないとき
    if( status_ < kFireMario )
    {
        status_ += 1;          // マリオ変身

        // スーパーマリオ
        if( status_ == kSuperMario )
        {
            rect_.top = kQuadruple;
            rect_.bottom = kDoubleSize;
        }
        // ファイアマリオ
        else if( status_ == kFireMario )
        {
            rect_.top = kOctuple;
            rect_.bottom = kDoubleSize;
        }

        // 高さを揃える
        if( past_status_ == kMario )
        {
            position_.y -= kSize;
            total_move_.y -= kSize;
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
        invincible_time_ = false;  // マリオ無敵カウント開始

        // マリオRect
        rect_.top = 0;
        rect_.bottom = kSize;
    }
    else if( past_status_ == kSuperMario )
    {
        status_ -= 1;              // マリオ退化
        invincible_ = false;       // マリオ無敵に変える
        invincible_time_ = false;  // マリオ無敵カウント開始

        // マリオRect
        rect_.top = 0;
        rect_.bottom = kSize;
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

// ゴールをした時の処理
void Player::ending()
{        
    // 向き反転までのカウント
    down_cnt_++;

    // 状態がマリオの時
    if( status_ == kMario )
    {
        if( total_move_.y < (kSize * 11 + kHalfSize) )
        {
            // ゆっくりとポストから降りる
            position_.y += kDownSpeed;
            total_move_.y += kDownSpeed;

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
        // 降りきった向きを変えポストの向こう側へ行く
        else if( !catch_flag_ && down_cnt_ >= kDownCnt )
        {
            if( !catch_flag_ )
            {
                catch_flag_ = true;
                position_.x += kSize;
                total_move_.x += kSize;
            }

            direction_ = false;
        }
        // 塔へ向かって歩き出す
        else if( down_cnt_ >= kTurnCnt )
        {
            if( total_move_.x < (kSize * kEntrance) - kHalfSize )
            {
                position_.x += 3;
                total_move_.x += 3;

                animation();

                if( position_.y < kEndLine )
                {
                    acceleration_ += kGravity;
                    position_.y += acceleration_;
                    total_move_.y += acceleration_;
                }
                else
                {
                    direction_ = true;
                    position_.y = kEndLine;
                }
            }
            else
                // 透明化
                extinguish_existence_ = false;
        }
    }
    // 体がマリオ以外の時
    else
        if( total_move_.y < (kDecuple + kHalfSize) )
        {
            // ポストから降りる
            position_.y += kDownSpeed;
            total_move_.y += kDownSpeed;

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
        // 向きを変えポストの向こう側へ
        else if( !catch_flag_ && down_cnt_ >= kDownCnt )
        {
            if( !catch_flag_ )
            {
                catch_flag_ = true;
                position_.x += kSize;
                total_move_.x += kSize;
            }

            direction_ = false;
        }
        // 塔へ向かって歩く
        else if(down_cnt_ >= kTurnCnt)
        {
            if( total_move_.x < (kSize * kEntrance) - kHalfSize )
            {
                position_.x += 3;
                total_move_.x += 3;

                // 歩くアニメーション
                animation();

                if( position_.y < kEndLine - kSize )
                {
                    acceleration_ += kGravity;
                    position_.y += acceleration_;
                    total_move_.y += acceleration_;
                }
                else
                {
                    direction_ = true;
                    position_.y = kEndLine - kSize;
                }
            }
            else
                // 体の透明化
                extinguish_existence_ = false;
        }
}

void Player::rightCheck()
{
    // 体の上下の確認
    body_[ kRight ][ kShoulder ][ kX ] = (total_move_.x + kSize + 1);
    body_[ kRight ][ kShoulder ][ kY ] = (total_move_.y);

    body_[ kRight ][ kHands ][ kX ] = (total_move_.x + kSize + 1);
    // status_がkMarioの時
    if( status_ == kMario )
        body_[ kRight ][ kHands ][ kY ] = (total_move_.y + kSize - 1);
    else
        body_[ kRight ][ kHands ][ kY ] = (total_move_.y + kDoubleSize - 1);


    // 当たり判定のないブロックのとき
    if( Collision::sideColl( kRight ) == true )
    {
        // kSuperMario以上の時体の真ん中をすり抜けないように確認
        if( status_ >= kSuperMario )
        {
            // 体の右側を登録
            body_[ kRight ][ kShoulder ][ kX ] = (total_move_.x + kSize + 1);
            body_[ kRight ][ kShoulder ][ kY ] = (total_move_.y + kSize);
        }

        // もう一度当たり判定を確認する
        if( Collision::sideColl( kRight ) == true )
        {
            // HELD中のとき
            if( push_time_run_ >= 2 )
            {
                // 右への移動
                position_.x += kDashSpeed;
                total_move_.x += kDashSpeed;
            }
            else
            {
                // 右への移動
                position_.x += kSpeed;
                total_move_.x += kSpeed;

            }

            // pos_x_ センターを超えるとき
            if( position_.x > kEndLine )
            {
                scroll_cnt_ = total_move_.x - kEndLine;
                position_.x = kEndLine;
            }
        }
    }
}

void Player::leftCheck()
{
    // 上と両サイドは変更なし
    body_[ kLeft ][ kShoulder ][ kX ] = (total_move_.x - 1);
    body_[ kLeft ][ kShoulder ][ kY ] = (total_move_.y);

    body_[ kLeft ][ kHands ][ kX ] = (total_move_.x - 1);

    // 下の位置だけ状態に応じて変更する
    if( status_ == kMario )
        body_[ kLeft ][ kHands ][ kY ] = (total_move_.y + kSize - 1);
    else
        body_[ kLeft ][ kHands ][ kY ] = (total_move_.y + kDoubleSize - 1);

    // マリオの左側に衝突するブロックがないとき
    if( Collision::sideColl( kLeft ) == true )
    {
        // 状態がスーパーマリオより上の時
        if( status_ >= kSuperMario )
        {
            // 体の左側を登録
            body_[ kLeft ][ kShoulder ][ kX ] = (total_move_.x - 1);
            body_[ kLeft ][ kShoulder ][ kY ] = (total_move_.y + kSize);
        }

        // もう一度当たり判定を確認する
        if( Collision::sideColl( kLeft ) == true )
        {
            if( push_time_run_ >= 2 )
            {
                // ポジションゼロより左の時
                if( position_.x <= 0 )
                    position_.x = 0;
                else
                {
                    position_.x -= kDashSpeed;
                    total_move_.x -= kDashSpeed;
                }
            }
            // 左壁以外の時
            else
            {   
                // ポジションゼロより左の時
                if( position_.x <= 0 )
                    position_.x = 0;
                else
                {
                    position_.x -= kSpeed;
                    total_move_.x -= kSpeed;
                }
            }
        }
    }
}

void Player::fireMove()
{
    // Status FireMario
    if( goal_flag_ )
    {
        if( throw_flag_ )
        {
            if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4) == 0 || CheckHitKey( KEY_INPUT_B ) == 1 )
                push_time_fire_++;
            else
                push_time_fire_ = 0;
        }

        // ファイアボールを投げるボタンの初回入力時
        if( push_time_fire_ == 1 )
            throw_flag_ = false;

        // 投げるが押されたとき
        if( !throw_flag_ )
        {
            throw_cnt_++;

            // 投げる切り取り範囲
            rect_.left   = kQuadruple;
            rect_.right  = kSize;
            rect_.top    = kDecuple;
            rect_.bottom = kDoubleSize;
        }
        else
        {
            // 投げないときは体の高さ戻す
            rect_.top    = kOctuple;
            rect_.bottom = kDoubleSize;
        }

        // 連続投射を防止する
        if( throw_cnt_ >= kStopper )
        {
            throw_cnt_ = 0;
            throw_flag_ = true;
        }
    }
}
