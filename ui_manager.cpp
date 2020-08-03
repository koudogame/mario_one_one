#include "share.hpp"
#include "ui_manager.hpp"

void UIManager::initialize()
{
    // 画像読み込み
    texture_ = LoadGraph( "texture/number.png" );  

    // 各種UI初期化
    map_.initialize();
    coin_.initialize();
    time_.initialize();
    score_.initialize();
}

void UIManager::update( bool GoalFlag )
{    
    // ゴール状態取得
    time_.setGoalFlag( GoalFlag );

    // 各種UI更新
    map_.update();
    coin_.update();
    time_.update();
    score_.update();
}

void UIManager::draw()
{
    // 各種UI描画
    map_.draw( texture_ );
    coin_.draw( texture_ );
    time_.draw( texture_ );
    score_.draw( texture_ );
}

void UIManager::finalize()
{
    // 画像破棄
    DeleteGraph( texture_ );

    // 各種UI破棄
    map_.finalize();
    coin_.finalize();
    time_.finalize();
    score_.finalize();
}

void UIManager::timeScore()
{
    // 時間を１減らしスコアを50増やす
    score_.changeTime(time_.getTime());

    // 減らした数値を返す
    time_.setTime( score_.getTime() );
}

void UIManager::coinCheck( int Coin )
{
    // コインのカウントアップ関数
    coin_.coinCounter( Coin );
}