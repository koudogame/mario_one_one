#include "ball_management.hpp"

void BallManagement::initialize()
{
    texture_ = LoadGraph( "Texture/mario_item.png" );
    push_create_fire_ = 0;

    create_cnt_ = 0;
    create_flag_ = true;
}

void BallManagement::update( int TotalX, int TotalY, int Status, int Direction, bool GameOver, int PosY )
{
    // マリオがゴールしていないとき
    if( GameOver )
    {
        // マリオが生存しているとき発射対象
        if( PosY <= kEndline )
        {
            // ボタンが押されたとき かつ、FireMarioの時
            if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4) == 0 )
                push_create_fire_++;
            else
                push_create_fire_ = 0;

            // ボタンが押されたとき
            if( push_create_fire_ == 1 )
            {
                size_t index = std::distance( fire_.begin(), fire_.end() );

                if( index <= 3 )
                    // まだ生成していなかったら作成
                    if( create_flag_ )
                    {
                        // ファイアマリオのとき
                        if( Status == 2 )
                        {
                            // 新しく追加して動かす
                            fire_.push_back( new FireFactory( field_ ) );
                            fire_.back()->initialize( TotalX, TotalY, Direction );

                            create_flag_ = false;
                        }
                    }

            }

            if( !create_flag_ )
                create_cnt_++;

            // 連続で出されないようにするため
            if( create_cnt_ >= kStopper )
            {
                create_cnt_ = 0;
                create_flag_ = true;
            }
        }


        // 要素数だけFireを動かす
        for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
        {
            (*itr)->update();                                 // *itrアロー演算子()をつける
        }
    }
}

void BallManagement::draw(const int ScreenOver)
{
    // 要素数だけFireを描画する
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->draw( texture_, ScreenOver );             // *itrアロー演算子()をつける
    }
}

void BallManagement::finalize()
{
    DeleteGraph( texture_ );
}

int BallManagement::getFirePosX(int Num)
{
        return fire_[Num]->getFirePosX();                 // *itrアロー演算子()をつける
}

int BallManagement::getFirePosY(int Num)
{
        return fire_[Num]->getFirePosY();                 // *itrアロー演算子()をつける
}

int BallManagement::getSize()
{
    return fire_.size();                                  // Fireの要素の数を返す
}

void BallManagement::sideCheck()
{
    for( auto itr = fire_.begin(); itr != fire_.end(); )
    {
        if( !(*itr)->getExplode() )
        {
            size_t index = std::distance( fire_.begin(), itr );
            SAFE_DELETE( fire_[ index ] );
            itr = fire_.erase( itr );                     // 詰めるとき（消すとき）
        }
        else
            itr++;                                        // 詰めないとき（消さないとき）
    }
}

void BallManagement::posCheck( const int ScrollCnt)
{
    // それぞれ自分で画面内にいるか確認を行う
    for( auto itr = fire_.begin(); itr != fire_.end();  )
    {
        // 画面外にFireballがあるとき
        if( !(*itr)->getCheckScreen( ScrollCnt ) )
        {
            size_t index = std::distance( fire_.begin(), itr );
            SAFE_DELETE( fire_[ index ] );
            itr = fire_.erase( itr );                     // 詰めるとき（消すとき）
        }
        else
            itr++;                                        // 詰めないとき（消さないとき）
    }
}

void BallManagement::enemyCollision( int Index )
{
    // 炎が敵と当たったとき消える処理を実行
    fire_[ Index ]->setFire( false );

    if( !fire_[ Index ]->getExplode() )
    {
        SAFE_DELETE( fire_[ Index ] );
        fire_.erase( fire_.begin() + Index );
    }
}