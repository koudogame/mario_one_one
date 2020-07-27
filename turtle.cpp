#include "turtle.hpp"

void Turtle::update( int ScreenOver )
{
    // 動き出しは15マス分前から
    if( ScreenOver > (enemy_parts_.x - (kSize * kMoveStart)) )
    {
        // 動きつづけるのは画面内にいるとき
        if( ScreenOver <= enemy_parts_.x + kSize )
        {
            // 焼かれていないか
            if( burn_ )
            {
                // 死んでいないか
                if( active_ )
                {
                    animation();                                // 歩くアニメーション
                    enemy_parts_.x += kSpeed * direction_;      // 常に進む
                }
                else if( !pushout_ && !active_ )
                {
                    enemy_parts_.x += kMaxSpeed * direction_;
                }

                // 足の登録
                body_[ kRight ][ kFoot ][ kX ] = (enemy_parts_.x + (kSize - kDisplace));
                body_[ kRight ][ kFoot ][ kY ] = (enemy_parts_.y + kSize + 1) + kQuadruple;

                body_[ kLeft ][ kFoot ][ kX ] = (enemy_parts_.x + kDisplace);
                body_[ kLeft ][ kFoot ][ kY ] = (enemy_parts_.y + kSize + 1) + kQuadruple;

                // 足場があるとき
                if( Collision::footColl() == 1 )
                {
                    jumping_ = kNoMove;
                    acceleration_ = 0;  // 落下速度

                    int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;
                    enemy_parts_.y = ((block_line - kControl) * kSize) - 1;

                    if( block_line >= kGroundArray )
                        enemy_parts_.y = kGround;
                }
                // 宙に浮いているとき
                else if( Collision::footColl() == 2 )
                {
                    jumping_ = kNoJump;

                    // 落下していないか
                    if( enemy_parts_.y > kFallOut )
                    {
                        // アイテムを消す処理を書く
                        jumping_ = kNoMove;

                        enemy_parts_.Id = kNoBlock;
                        RECT rect;
                        rect.top = enemy_parts_.Id / kLength * kSize;
                        rect.left = enemy_parts_.Id % kLength * kSize;
                        rect.bottom = kSize;
                        rect.right = kSize;
                        enemy_parts_.rect = rect;
                    }

                    // 宙に浮いているとき落下
                    if( jumping_ == kNoJump )
                    {
                        acceleration_ += kGravity;
                        enemy_parts_.y += acceleration_;
                    }
                }

                // 右手の登録
                body_[ kRight ][ kShoulder ][ kX ] = (enemy_parts_.x + kSize + 1);
                body_[ kRight ][ kShoulder ][ kY ] = (enemy_parts_.y + kGather) + kQuadruple;
                body_[ kRight ][ kHands ][ kX ] = (enemy_parts_.x + kSize + 1);
                body_[ kRight ][ kHands ][ kY ] = (enemy_parts_.y - kGather) + kQuadruple;

                // 当たり判定のあるとき
                if( Collision::sideColl( kRight ) == false )
                    direction_ *= -1;

                // 左手の登録
                body_[ kLeft ][ kShoulder ][ kX ] = (enemy_parts_.x - 1);
                body_[ kLeft ][ kShoulder ][ kY ] = (enemy_parts_.y + kGather) + kQuadruple;
                body_[ kLeft ][ kHands ][ kX ] = (enemy_parts_.x - 1);
                body_[ kLeft ][ kHands ][ kY ] = (enemy_parts_.y - kGather) + kQuadruple;

                // 当たり判定のあるとき
                if( Collision::sideColl( kLeft ) == false )
                    direction_ *= -1;
            }
            // 甲羅状態での落下
            else
            if( enemy_parts_.y < kFieldSize )
            {
                enemy_parts_.rect.left = kSize;
                enemy_parts_.rect.top = kSeptuple;
                enemy_parts_.rect.right = kSize;
                enemy_parts_.rect.bottom = kSize;


                // 重力を反映させながら落下
                acceleration_ += kGravity;

                enemy_parts_.x += 2;
                enemy_parts_.y += acceleration_;
            }
        }
    }
}

int Turtle::getPosX()
{
    if(burn_)
    return (enemy_parts_.x - 1);

    return 0;
}

int Turtle::getPosY()
{
    if(burn_)
    return (enemy_parts_.y - 1) + kQuadruple;

    return 0;
}

// マリオと衝突したとき
void Turtle::posCollision( int Touch )
{
    if( Touch == 1 )
    {
        // 起きてるときに叩いたら
        if( active_ )
        {
            enemy_parts_.Id = kShell;
            RECT rect;
            rect.top = kShell / kLength * kSize;
            rect.left = kShell % kLength * kSize;
            rect.bottom = kSize;
            rect.right = kSize;
            enemy_parts_.rect = rect;

            active_ = false;          // 甲羅の中に入る
        }
    }
    else if( Touch == 2 )
    {
        pushout_    = false;
        direction_  = 1;
        action_cnt_ = 1;

        enemy_parts_.x += kPushSpeed;
    }
    else if( Touch == 3 )
    {
        pushout_    = false;
        direction_  = -1;
        action_cnt_ = 1;

        enemy_parts_.x -= kPushSpeed;
    }
}

// 甲羅状態で衝突した時
void Turtle::shellCollision()
{
    ++action_cnt_;

    if( action_cnt_ == 1 )
    {
        pushout_ = false;
        direction_ = 1;
    }
    else if( action_cnt_ == 3 )
    {
        pushout_ = true;
        action_cnt_ = 0;
    }
}

// ファイアと衝突したとき
void Turtle::fireCollision()
{
    EnemyBase::fireCollision();

    enemy_parts_.rect.left = kSize;
    enemy_parts_.rect.top = kSeptuple;
    enemy_parts_.rect.right = kSize;
    enemy_parts_.rect.bottom = kSize;
}

// 歩くアニメーション
void Turtle::animation()
{
    animation_++;

    if( animation_ > kCountup )
    {
        animation_ = 0;
        walk_animation_ *= -1;
    }

    if( walk_animation_ == -1 )
    {
        enemy_parts_.rect.left = kQuadruple;
        enemy_parts_.rect.right = kSize;
    }
    else
    {
        enemy_parts_.rect.left = Quintuple;
        enemy_parts_.rect.right = kSize;
    }

    enemy_parts_.rect.top = kDoubleSize;
    enemy_parts_.rect.bottom = static_cast<int>(kSize * 1.5);
}
