#include "play.hpp"
#include "scene_manager.hpp"

PlayScene::PlayScene()
{
    // クラスポインタ初期化
    item_ = nullptr;
    field_ = nullptr;
    player_ = nullptr;
}

PlayScene::~PlayScene()
{
}

bool PlayScene::initialize()
{
    // インスタンスの生成
    item_ = new Item();
    field_ = new Field();
    player_ = new Player(field_);

    // ファイルに対する入力ストリーム
    std::fstream stage;
    std::fstream item;

    // 入力のためにオープンする入出力をバイナリで行う
    stage.open( "mario_field.fmf", std::ios_base::in | std::ios_base::binary );
    item.open( "mario_item.fmf", std::ios_base::in | std::ios_base::binary );

    // クラス内の初期化を行う
    item_->initialize( item );
    field_->initialize( stage );
    player_->initialize();

    return true;
}

void PlayScene::update()
{    
    player_->update();
    field_->update(player_->getBreakRightX(), player_->getBreakRightY(),
        player_->getBreakLeftX(), player_->getBreakLeftY(), player_->getStatus());
    item_->update( player_->getBreakRightX(), player_->getBreakRightY(),
        player_->getBreakLeftX(), player_->getBreakLeftY(), player_->getStatus());
}

void PlayScene::draw()
{
    item_->draw(player_->getScrollCnt());
    field_->draw(player_->getScrollCnt());
    player_->draw();
}

void PlayScene::finalize()
{
    // DeleteGraphなど
    item_->finalize();
    field_->finalize();
    player_->finalize();

    // メモリ開放newした分]
    delete item_;
    delete field_;
    delete player_;
}