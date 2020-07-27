#include "ball_management.hpp"

void BallManagement::initialize()
{
    texture_          = LoadGraph( "Texture/mario_item.png" );
    push_create_fire_ = 0;

    create_cnt_       = 0;
    create_flag_      = true;
}

void BallManagement::update( int TotalX, int TotalY, int Status, int Direction, bool GameOver, int PosY )
{
    // 発射可能状態
    if( GameOver && PosY <= kEndline )
    {
        // ボタンが押されたとき
        if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_4) == 0 || CheckHitKey( KEY_INPUT_B ) == 1 )
            push_create_fire_++;
        else
            push_create_fire_ = 0; // 押されていない間初期化


        // ボタンが押された瞬間
        if( push_create_fire_ == 1 )
            createFire( TotalX, TotalY, Status, Direction );

        // 時間管理
        if( !create_flag_ )
            create_cnt_++;

        // 連投を一定間隔に制御
        if( create_cnt_ >= kStopper )
        {
            create_cnt_ = 0;
            create_flag_ = true;
        }
    }

    // 要素数だけFireBallのupdate()を呼び出す
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->update();
    }
}

void BallManagement::draw(const int ScreenOver)
{
    // 要素数だけFireBallのdraw()を呼び出す
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->draw( texture_, ScreenOver );
    }
}

void BallManagement::finalize()
{
    DeleteGraph( texture_ );
}

int BallManagement::getFirePosX(int Num)
{
        return fire_[Num]->getFirePosX();
}

int BallManagement::getFirePosY(int Num)
{
        return fire_[Num]->getFirePosY();
}

int BallManagement::getSize()
{
    return static_cast<int>(fire_.size());                // Fireの要素の数を返す
}

// 新しく生成する処理
void BallManagement::createFire( int TotalX, int TotalY, int Status, int Direction )
{
    size_t index = std::distance( fire_.begin(), fire_.end() );

    // ４個まで同時投射可能
    if( index < kBallLimit )
    {
        // まだ生成していなかったら作成
        if( create_flag_ )
        {
            // ファイアマリオのとき
            if( Status == kFireMario )
            {
                // 新しく追加して動かす
                fire_.push_back( new FireFactory( field_ ) );
                fire_.back()->initialize( TotalX, TotalY, Direction );

                create_flag_ = false;
            }
        }
    }
}


void BallManagement::sideCheck()
{
    for( auto itr = fire_.begin(); itr != fire_.end(); )
    {
        if( !(*itr)->getExplode() )
        {
            size_t index = std::distance( fire_.begin(), itr );
            SAFE_DELETE( fire_[ index ] );
            itr = fire_.erase( itr );   // 詰めるとき（消すとき）
        }
        else
            itr++;                      // 詰めないとき（消さないとき）
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
            // 配列の先頭から位置を計算し破棄する
            size_t index = std::distance( fire_.begin(), itr );
            SAFE_DELETE( fire_[ index ] );
            itr = fire_.erase( itr );   // 詰めるとき（消すとき）
        }
        else
            itr++;                      // 詰めないとき（消さないとき）
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