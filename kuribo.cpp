#include "kuribo.hpp"

void Kuribo::update( int ScreenOver )
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
                // 踏まれていないか
                if( alive_ )
                {
                    animation();                                // 歩くアニメーション
                    enemy_parts_.x += kSpeed * direction_;      // 常に進む


                    // 足の登録
                    body_[ kRight ][ kFoot ][ kX ] = (enemy_parts_.x + (kSize - kDisplace));
                    body_[ kRight ][ kFoot ][ kY ] = (enemy_parts_.y + kSize + 1) + kQuadruple;

                    body_[ kLeft ][ kFoot ][ kX ] = (enemy_parts_.x + kDisplace);
                    body_[ kLeft ][ kFoot ][ kY ] = (enemy_parts_.y + kSize + 1) + kQuadruple;

                    // 足場があるとき
                    if( Collision::footColl() == 1 )
                    {
                        jumping_ = kNoMove;

                        int block_line = (body_[ kRight ][ kFoot ][ kY ] - 1) / kSize;

                        // 足元が埋まっていないか
                        if( block_line >= kGroundArray )
                            enemy_parts_.y = kGround;
                        else
                        enemy_parts_.y = ((block_line - kControl) * kSize) - kSize;


                        acceleration_ = 0;  // 落下速度
                    }
                    // 宙に浮いているとき
                    else if( Collision::footColl() == 2 )
                    {
                        jumping_ = kNoJump;

                        // 穴に落下したとき
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
                else
                {
                    // 踏まれた後に消えるまで
                    if( death_cnt_ < kDeathTime )
                    {
                        death_cnt_++;
                    }
                    else
                    {
                        enemy_parts_.Id = kNoBlock;
                        RECT rect;
                        rect.top = enemy_parts_.Id / kLength * kSize;
                        rect.left = enemy_parts_.Id % kLength * kSize;
                        rect.bottom = kSize;
                        rect.right = kSize;
                        enemy_parts_.rect = rect;
                    }
                }
            }
            // 焼かれたときの処理
            else
            {
                // 決められた位置まで落下させる
                if( enemy_parts_.y < kFieldSize )
                {
                    // 重力を反映させながら落下
                    acceleration_ += kGravity;

                    enemy_parts_.x += 2;
                    enemy_parts_.y += acceleration_;
                }
            }
        }
    }
}

int Kuribo::getPosX()
{
    if(burn_)
    return (enemy_parts_.x - 1);

    return 0;
}

int Kuribo::getPosY()
{
    if( burn_ )
        return (enemy_parts_.y - 1) + kQuadruple;
    
    return 0;
}

// マリオとの衝突があったとき
void Kuribo::posCollision(int Touch)
{
    // アイテムを消す処理を書く
    jumping_ = kNoMove;

    enemy_parts_.Id = kDead;
    RECT rect;
    rect.top = enemy_parts_.Id / kLength * kSize;
    rect.left = enemy_parts_.Id % kLength * kSize;
    rect.bottom = kSize;
    rect.right = kSize;
    enemy_parts_.rect = rect;
    enemy_parts_.y += kDown;

    alive_ = false;
}

// 歩くアニメーション
void Kuribo::animation()
{
    animation_++;

    if( animation_ > kCountup )
    {
        animation_ = 0;
        walk_animation_ *= -1;
    }

    if( walk_animation_ == -1 )
    {
        enemy_parts_.rect.left = 0;
        enemy_parts_.rect.right = kSize;
    }
    else
    {
        enemy_parts_.rect.left = kSize;
        enemy_parts_.rect.right = kSize;
    }
}
