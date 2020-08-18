#include "player.hpp"

bool Player::initialize()
{
    texture_          = LoadGraph( "Texture/mario_anime.png" );
    data_.player_position.x       = kStartX;
    data_.player_position.y       = kStartY;
  
    // ゲーム開始時のRECT
    defaultSize( kMario );
 
    // 開始時data_.player_statusがkMario以外なら
    if( data_.player_status != kMario )
    {
        data_.player_position.y -= kSize;
        data_.total_position.y -= kSize;
    }
    
    // 数値の中のポジション
    data_.total_position.x = kStartX;
    data_.total_position.y = 832;

    data_.player_status           = kMario;
    past_status_      = data_.player_status;

    data_.scroll_cnt       = 0;            // 右に抜けた分増やしていく

    data_.gameover_flag    = true;         // これが立ったら死ぬ

    animation_        = 0;            // 立っているだけの状態
    data_.direction        = true;         // 初期は右向き

    animation_cnt_    = 0;            // 何もしていないときは動かない
    animation_flag_   = true;         // ジャンプしているとき以外は移動時アニメーション

    old_right_button_ = true;
    old_left_button_  = true;
    old_down_button_  = true;

    right_button_     = true;
    left_button_      = true;

    acceleration_     = 0;
    jumping_          = kJump;

    data_.invincible_flag       = true;
    invincible_time_  = true;
    invincible_cnt_   = 0;

    data_.goal_flag        = true;
    catch_flag_       = true;
    data_.end_flag = true;

    throw_cnt_ = 0;
    throw_flag_ = true;

    down_cnt_         = 0;

    push_time_jump_ = 0;
    push_time_fire_ = 0;
    push_time_run_  = 0;
    data_.push_squat= 0;

    speed_ = 0;
    speed_up_ = 0;
    speed_down_ = 0;
    sliding_ = true;

    return true;
}

bool Player::update( bool TimeLimit )
{
    if( !data_.goal_flag ) ending();
    else if( data_.gameover_flag )
    {
        if( invincible_time_ )
        {
            // しゃがめる大きさかどうか
            if( data_.player_status > kMario && data_.goal_flag )
                squat();

            // ダッシュボタン判定
            if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4) == 0 || CheckHitKey( KEY_INPUT_B ) == 1 )
                push_time_run_++;
            else
                push_time_run_ = 0;

            if( left_button_ )
            {
                // 右入力
                if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_RIGHT) == 0 || CheckHitKey( KEY_INPUT_D ) == 1 )
                    rightPush();
                else
                    right_button_ = true;
            }

            if( right_button_ )
            {
                // 左入力
                if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_LEFT) == 0 || CheckHitKey( KEY_INPUT_A ) == 1 )
                    leftPush();
                else
                    left_button_ = true;
            }

            // 右への移動時
            if( speed_ > 0 )
                rightCheck();

            // 左への移動時
            if( speed_ < 0 )
                leftCheck();

            // スピードはあるがボタンは押していない時は0にする
            if( speed_ != 0 && right_button_ && left_button_ )
            {
                speed_down_++;

                if( speed_down_ >= 2 )
                {
                    if( speed_ > 0 )
                        speed_--;
                    if( speed_ < 0 )
                        speed_++;

                    speed_down_ = 0;
                }
            }

            // しゃがんでいなかったらアニメーション
            if( data_.push_squat == 0 && speed_ != 0 )
                animation();

            if( data_.push_squat == 0 && speed_ == 0 )
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
                if( jumping_ == kJump )
                {
                    timekeep_squat_ = data_.push_squat;
                    jumping_ = kNoJump;
                    acceleration_ = -kJumpPower;

                    // ジャンプ中にアニメーションを動かさないようにする
                    animation_flag_ = false;

                    // ジャンプRECTに切り替え
                    // kMario状態の時のみ有効
                    if( timekeep_squat_ == 0 )
                        animation_ = 4;
                }
            }

            // ジャンプをした時重力をかける
            if( jumping_ == kNoJump )
            {
                acceleration_ += kGravity;

                // マリオを飛ばす
                data_.player_position.y += acceleration_;
                data_.total_position.y += acceleration_;
            }

            // 加速度上限
            if( acceleration_ >= 20 )
            {
                acceleration_ = 20;
            }

            // しゃがみ状態のみ頭の位置を下げる
            if( data_.push_squat == 0 )
            {
                // マリオの頭(幅を左右10小さく)
                body_[ kRight ][ kHead ][ kX ] = (data_.total_position.x + (kSize - kGather));
                body_[ kRight ][ kHead ][ kY ] = (data_.total_position.y - 1);
                body_[ kLeft ][ kHead ][ kX ] = (data_.total_position.x + kGather);
                body_[ kLeft ][ kHead ][ kY ] = (data_.total_position.y - 1);
            }
            else
            {
                // マリオの頭(幅を左右10小さく)
                body_[ kRight ][ kHead ][ kX ] = (data_.total_position.x + (kSize - kGather));
                body_[ kRight ][ kHead ][ kY ] = (data_.total_position.y + kSize - 1);
                body_[ kLeft ][ kHead ][ kX ] = (data_.total_position.x + kGather);
                body_[ kLeft ][ kHead ][ kY ] = (data_.total_position.y + kSize - 1);
            }

            // マリオの足元
            body_[ kRight ][ kFoot ][ kX ] = (data_.total_position.x + (kSize - kGather));
            body_[ kLeft ][ kFoot ][ kX ] = (data_.total_position.x + kGather);

            // マリオの時
            if( data_.player_status == kMario )
            {
                body_[ kRight ][ kFoot ][ kY ] = (data_.total_position.y + kSize + 1);
                body_[ kLeft ][ kFoot ][ kY ] = (data_.total_position.y + kSize + 1);
            }
            // マリオ以外の時
            else
            {
                body_[ kRight ][ kFoot ][ kY ] = (data_.total_position.y + kDoubleSize + 1);
                body_[ kLeft ][ kFoot ][ kY ] = (data_.total_position.y + kDoubleSize + 1);
            }

            // 上へ飛んでいるときにだけhit()を呼ぶ
            if( acceleration_ < 0 )
            {
                // しゃがみ時
                if( data_.push_squat == 0 )
                {
                    // 右頭にあたるとき
                    if( Collision::collision( kRight, kHead ) <= kSize )
                    {
                        data_.break_right.x = (data_.total_position.x / kSize) + 1;
                        data_.break_right.y = data_.total_position.y / kSize;
                    }
                    // 左頭にあたるとき
                    if( Collision::collision( kLeft, kHead ) <= kSize )
                    {
                        data_.break_left.x = (data_.total_position.x / kSize);
                        data_.break_left.y = data_.total_position.y / kSize;
                    }
                }
                else
                {
                    // 右頭にあたるとき
                    if( Collision::collision( kRight, kHead ) <= kSize )
                    {
                        data_.break_right.x = (data_.total_position.x / kSize) + 1;
                        data_.break_right.y = (data_.total_position.y + kSize) / kSize;
                    }
                    // 左頭にあたるとき
                    if( Collision::collision( kLeft, kHead ) <= kSize )
                    {
                        data_.break_left.x = (data_.total_position.x / kSize);
                        data_.break_left.y = (data_.total_position.y + kSize) / kSize;
                    }
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
                // 足元の衝突判定
                collision();

            // ゴール
            if( data_.total_position.x >= (kSize * kGoalPost) + kHalfSize )
            {
                animation_flag_ = true;
                catch_flag_ = false;
                data_.goal_flag = false;
                animation_ = 6;
                acceleration_ = 0;
                data_.total_position.x = (kSize * kGoalPost) + kHalfSize;
            }

            // 時間制限による死亡
            if( !TimeLimit )
            {
                data_.gameover_flag = false;
                acceleration_ = -kJumpPower;
                data_.player_status = kGameover;
            }
        }

        // 無敵時間制限
        if( !data_.invincible_flag )
        {
            invincible_cnt_++;

            // ９回拡縮したら解放
            if( invincible_cnt_ > kAnimeMove * kAnimeMove )
                invincible_time_ = true;

            // 時間が来たら無敵解除
            if( invincible_cnt_ > kInvincible )
            {
                invincible_cnt_ = 0;
                data_.invincible_flag = true;
            }
        }
    }
    // 死んでいるとき
    else
    {
        // 落ちたとき演出無く死亡
        if( data_.player_position.y > kDeadLine )
            return false;

        // data_.player_statusがマイナスの時
        // GameOver Action
        acceleration_ += kGravity;

        // マリオを飛ばす
        data_.player_position.y += acceleration_;
        data_.total_position.y += acceleration_;
    }

    return true;
}

void Player::draw()
{
    // ゴール前
    if( data_.end_flag )
    {
        // 頭の初期化
        data_.break_left.x = 0; data_.break_left.y = 0;
        data_.break_right.x = 0; data_.break_right.y = 0;

        // 共通範囲(しゃがんでいない時)
        if( data_.push_squat == 0 )
        {
            rect_.left = animation_ * kSize;
            rect_.right = kSize;
        }

        // やられるとき
        if( data_.player_status == kGameover )
            defaultSize( kGameover );

        // ファイアマリオ
        else if( data_.player_status == kFireMario && data_.push_squat == 0 )
            fireMove();

        // RECTのずれが発生しないように
        if( data_.player_status == kFireMario && !data_.goal_flag )
            defaultSize( kFireMario );

        // 無敵状態(半透明)
        if( !data_.invincible_flag && data_.player_status != kGameover )
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
                    defaultSize( kMario );

                    // 高さを揃える
                    data_.player_position.y += kSize;
                    data_.total_position.y += kSize;
                }
                // 余り０で奇数の時
                else if( m == 0 && n % 2 == 1 )
                {
                    // Rectを切り替える
                    defaultSize( kSuperMario );

                    // 高さを揃える
                    data_.player_position.y -= kSize;
                    data_.total_position.y -= kSize;
                }
            }
        }

        // 滑っているときだけ反転
        if( animation_ == kSliding )
        {
            if( data_.direction )
                data_.direction = false;
            else
                data_.direction = true;
        }

        // 通常描画
        DrawRectGraph( data_.player_position.x, data_.player_position.y,
            rect_.left, rect_.top, rect_.right, rect_.bottom,
            texture_, TRUE, !data_.direction );

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
    if( animation_flag_ && sliding_ )
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
    int fool_col = Collision::footColl();

    // 足元にあるブロックが乗れるとき
    if( fool_col == 1 )
    {
        landing();          // 着地処理

        acceleration_ = 0;  // 落下速度

        int block_line = static_cast<int>(std::round( static_cast<float>(data_.total_position.y) / kSize ));
        data_.player_position.y = (block_line - kControl) * kSize;
        data_.total_position.y = block_line * kSize;
    }
    // 足元に何もなく浮いているとき
    else if( fool_col == 2 )
    {
        // 時間を保存
        timekeep_squat_ = data_.push_squat;

        // 落下中に動かないように
        animation_flag_ = false;

        // 飛べないようにする
        jumping_ = kNoJump;

        // マリオが画面外に行ったとき
        if( data_.player_position.y > kFallOut )
        {
            // gameover
            data_.gameover_flag = false;
        }
    }
}

// 着地したタイミング
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

    int block_line = static_cast<int>(std::round( static_cast<float>(data_.total_position.y) / kSize ));

    // プレイヤーの立つ場所を上の辺の高さにする
    data_.player_position.y = (block_line - kControl) * kSize;
    data_.total_position.y = block_line * kSize;
}

void Player::itemCollision()
{
    // 最終進化じゃないとき
    if( data_.player_status < kFireMario )
    {
        data_.player_status += 1;          // マリオ変身

        // スーパーマリオ
        if( data_.player_status == kSuperMario )
            defaultSize( kSuperMario );

        // ファイアマリオ
        else if( data_.player_status == kFireMario )
            defaultSize( kFireMario );

        // 高さを揃える
        if( past_status_ == kMario )
        {
            data_.player_position.y -= kSize;
            data_.total_position.y -= kSize;
        }

        // 変身後の状態を保存
        past_status_ = data_.player_status;
    }
}

void Player::enemyCollision()
{
    if( past_status_ > kMario )
    {
        data_.player_status = kMario;           // マリオ退化
        data_.invincible_flag = false;        // マリオ無敵に変える
        invincible_time_ = false;   // マリオ無敵カウント開始

        if( data_.push_squat != 0 )
        {
            defaultSize( kMario );
            data_.push_squat = 0;
        }
    }
    else
    {
        data_.player_status = kGameover;        // マリオ死亡
        data_.gameover_flag = false;     // ゲームオーバー
        acceleration_ = -kJumpPower;// 跳ねるアクション
    }

    past_status_ = data_.player_status;         // 変身後の状態を保存
}

void Player::enemyStepon()
{    
    // しゃがんでいない時
    if(data_.push_squat == 0)
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
    if( data_.player_status == kMario )
    {
        if( data_.total_position.y < (kSize * 11 + kHalfSize) )
        {
            // ゆっくりとポストから降りる
            data_.player_position.y += kDownSpeed;
            data_.total_position.y += kDownSpeed;

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
                data_.player_position.x += kSize;
                data_.total_position.x += kSize;
            }

            data_.direction = false;
        }
        // 塔へ向かって歩き出す
        else if( down_cnt_ >= kTurnCnt )
        {
            if( data_.total_position.x < (kSize * kEntrance) - kHalfSize )
            {
                data_.player_position.x += 3;
                data_.total_position.x += 3;

                animation();

                if( data_.player_position.y < kEndLine )
                {
                    acceleration_ += kGravity;
                    data_.player_position.y += acceleration_;
                    data_.total_position.y += acceleration_;
                }
                else
                {
                    data_.direction = true;
                    data_.player_position.y = kEndLine;
                }
            }
            else
                // 透明化
                data_.end_flag = false;
        }
    }
    // 体がマリオ以外の時
    else
        if( data_.total_position.y < (kDecuple + kHalfSize) )
        {
            // ポストから降りる
            data_.player_position.y += kDownSpeed;
            data_.total_position.y += kDownSpeed;

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
                data_.player_position.x += kSize;
                data_.total_position.x += kSize;
            }

            data_.direction = false;
        }
        // 塔へ向かって歩く
        else if(down_cnt_ >= kTurnCnt)
        {
            if( data_.total_position.x < (kSize * kEntrance) - kHalfSize )
            {
                data_.player_position.x += 3;
                data_.total_position.x += 3;

                // 歩くアニメーション
                animation();

                if( data_.player_position.y < kEndLine - kSize )
                {
                    acceleration_ += kGravity;
                    data_.player_position.y += acceleration_;
                    data_.total_position.y += acceleration_;
                }
                else
                {
                    data_.direction = true;
                    data_.player_position.y = kEndLine - kSize;
                }
            }
            else
                // 体の透明化
                data_.end_flag = false;
        }
}

void Player::rightCheck()
{
    // 体の上下の確認
    body_[ kRight ][ kShoulder ][ kX ] = (data_.total_position.x + kSize + 1);
    body_[ kRight ][ kShoulder ][ kY ] = (data_.total_position.y);

    body_[ kRight ][ kHands ][ kX ] = (data_.total_position.x + kSize + 1);
    // data_.player_statusがkMarioの時
    if( data_.player_status == kMario )
        body_[ kRight ][ kHands ][ kY ] = (data_.total_position.y + kSize - 1);
    else
        body_[ kRight ][ kHands ][ kY ] = (data_.total_position.y + kDoubleSize - 1);


    // 当たり判定のないブロックのとき
    if( Collision::sideColl( kRight ) == true )
    {
        // kSuperMario以上の時体の真ん中をすり抜けないように確認
        if( data_.player_status >= kSuperMario )
        {
            // 体の右側を登録
            body_[ kRight ][ kShoulder ][ kX ] = (data_.total_position.x + kSize + 1);
            body_[ kRight ][ kShoulder ][ kY ] = (data_.total_position.y + kSize);
        }

        // もう一度当たり判定を確認する
        if( Collision::sideColl( kRight ) == true )
        {
            data_.player_position.x += speed_;
            data_.total_position.x += speed_;

            // pos_x_ センターを超えるとき
            if( data_.player_position.x > kEndLine )
            {
                data_.scroll_cnt = data_.total_position.x - kEndLine;
                data_.player_position.x = kEndLine;
            }
        }
    }
}

void Player::leftCheck()
{
    // 上と両サイドは変更なし
    body_[ kLeft ][ kShoulder ][ kX ] = (data_.total_position.x - 1);
    body_[ kLeft ][ kShoulder ][ kY ] = (data_.total_position.y);

    body_[ kLeft ][ kHands ][ kX ] = (data_.total_position.x - 1);

    // 下の位置だけ状態に応じて変更する
    if( data_.player_status == kMario )
        body_[ kLeft ][ kHands ][ kY ] = (data_.total_position.y + kSize - 1);
    else
        body_[ kLeft ][ kHands ][ kY ] = (data_.total_position.y + kDoubleSize - 1);

    // マリオの左側に衝突するブロックがないとき
    if( Collision::sideColl( kLeft ) == true )
    {
        // 状態がスーパーマリオより上の時
        if( data_.player_status >= kSuperMario )
        {
            // 体の左側を登録
            body_[ kLeft ][ kShoulder ][ kX ] = (data_.total_position.x - 1);
            body_[ kLeft ][ kShoulder ][ kY ] = (data_.total_position.y + kSize);
        }

        // もう一度当たり判定を確認する
        if( Collision::sideColl( kLeft ) == true )
        {
                // ポジションゼロより左の時
                if( data_.player_position.x <= 0 )
                    data_.player_position.x = 0;
                else
                {
                    data_.player_position.x += speed_;
                    data_.total_position.x += speed_;
                }
        }
    }
}

// しゃがみ動作
void Player::squat()
{
    // 下が押されたとき
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_DOWN) == 0 || CheckHitKey( KEY_INPUT_S ) == 1 )
        data_.push_squat++;
    else
    {
            defaultSize( data_.player_status );
            data_.push_squat = 0;
    }

    // ジャンプした瞬間の状態をキープ
    if( !animation_flag_ )
        data_.push_squat = timekeep_squat_;

    // しゃがみが押されたときRECT切り替え
    if( data_.push_squat >= 1 )
    {
        if( data_.player_status == kSuperMario )
            rect_.top = kSextuple;

        else if( data_.player_status == kFireMario )
            rect_.top = kDecuple;

        rect_.left = 0;
        rect_.right = kSize;
        rect_.bottom = kDoubleSize;
    }
}

void Player::fireMove()
{
    // Status FireMario
    if( data_.goal_flag )
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
            rect_.left = kQuadruple;
            rect_.right = kSize;
            rect_.top = kDecuple;
            rect_.bottom = kDoubleSize;
        }
        else
            defaultSize( kFireMario );

        // 連続投射を防止する
        if( throw_cnt_ >= kStopper )
        {
            throw_cnt_ = 0;
            throw_flag_ = true;
        }
    }
}

// RECT登録
void Player::defaultSize( int Status )
{
    // ゲームオーバー
    if( Status == kGameover )
    {        
        rect_.left   = 0;
        rect_.right  = kSize;
        rect_.top    = kSize;
        rect_.bottom = kSize;
    }
    // マリオ
    else if( Status == kMario )
    {
        rect_.top    = 0;
        rect_.bottom = kSize;
    }
    // スーパーマリオ
    else if( Status == kSuperMario )
    { 
        rect_.top = kQuadruple;
        rect_.bottom = kDoubleSize;
    }
    // ファイアマリオ
    else if( Status == kFireMario )
    {
        rect_.top = kOctuple;
        rect_.bottom = kDoubleSize;
    }
}

void Player::rightPush()
{
    data_.direction = true;         // 向きを右向きに変える
    right_button_ = false;     // 押している(トラッカー) 

    if( data_.push_squat == 0 )
    {           
        speed_up_++;

        // ダッシュ押されている時
        if( push_time_run_ != 0 )
        {
            if( speed_up_ >= 2 )
            {
                if( speed_ < kDashSpeed )
                    speed_++;

                if( speed_ < 0 )
                {
                    sliding_ = false;
                    animation_ = kSliding;
                }
                else
                    sliding_ = true;

                speed_up_ = 0;
            }
        }
        // ダッシュ押されていない時
        else
        {
            if( speed_ > kSpeed )
                speed_ = kSpeed;

            if( speed_up_ >= 2 )
            {
                if( speed_ < kSpeed )
                    speed_++;

                if( speed_ < 0 )
                {
                    sliding_ = false;
                    animation_ = kSliding;
                }
                else
                    sliding_ = true;

                speed_up_ = 0;
            }
        }
    }
    else
    {
        speed_down_++;

        if( speed_down_ >= 2 )
        {
            if( speed_ > 0 )
                speed_--;
            if( speed_ < 0 )
                speed_++;

            speed_down_ = 0;
        }
    }
}

void Player::leftPush()
{
    data_.direction = false;        // 向きを左向きに変える
    left_button_ = false;      // 押している(トラッカー)

    if( data_.push_squat == 0 )
    {
        speed_up_++;

        // ダッシュ押されている時
        if( push_time_run_ != 0 )
        {
            if( speed_up_ >= 2 )
            {
                if( speed_ > -kDashSpeed )
                    speed_--;

                if( speed_ > 0 )
                {
                    sliding_ = false;
                    animation_ = kSliding;
                }
                else
                    sliding_ = true;

                speed_up_ = 0;
            }
        }
        // ダッシュ押されていない時
        else
        {
            if( speed_ < -kSpeed )
                speed_ = -kSpeed;

            if( speed_up_ >= 2 )
            {
                if( speed_ > -kSpeed )
                    speed_--;

                if(speed_ > 0)
                {
                    sliding_ = false;
                    animation_ = kSliding;
                }
                else
                    sliding_ = true;

                speed_up_ = 0;
            }
        }
    }
    // しゃがんでいる時
    else
    {
        speed_down_++;

        if( speed_down_ >= 2 )
        {
            if( speed_ > 0 )
                speed_--;
            if( speed_ < 0 )
                speed_++;

            speed_down_ = 0;
        }
    }
}

PlayerData Player::getData()
{
    return data_;
}