#include "ball_management.hpp"

void BallManagement::initialize()
{
    texture_ = LoadGraph( "Texture/mario_item.png" );
}

void BallManagement::update( int PosX, int PosY, int Status, int Direction )
{
    // ボタンが押されたとき
    // かつ、FireMarioの時
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_X) == 0 )
    {
        if( Status == 2 )
        {
            // 新しく追加して動かす
            fire_.push_back( new FireFactory( field_ ) );
            fire_.back()->initialize( PosX, PosY, Direction );
        }
    }

    // 要素数だけFireを動かす
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->update();                            // *itrアロー演算子()をつける
    }
}

void BallManagement::draw(const int ScreenOver)
{
    // 要素数だけFireを描画する
    for( auto itr = fire_.begin(); itr != fire_.end(); itr++ )
    {
        (*itr)->draw( texture_, ScreenOver );        // *itrアロー演算子()をつける
    }
}

void BallManagement::finalize()
{
    DeleteGraph( texture_ );
}
