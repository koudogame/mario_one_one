#include "play.hpp"
#include "scene_manager.hpp"

PlayScene::PlayScene()
{
    // クラスポインタ初期化
    field_ = nullptr;
    player_ = nullptr;
}

PlayScene::~PlayScene()
{
}

bool PlayScene::initialize()
{
    // インスタンスの生成
    field_ = new Field();
    player_ = new Player();

    // ファイルに対する入力ストリーム
    std::fstream stage;

    // 入力のためにオープンする入出力をバイナリで行う
    stage.open( "mario.fmf", std::ios_base::in | std::ios_base::binary );

    // クラス内の初期化を行う
    field_->initialize( stage );
    player_->initialize();

    return true;
}

void PlayScene::update()
{
    field_->update();
    player_->update();
}

void PlayScene::draw()
{
    field_->draw(0/*ここにScreenOver*/);
    player_->draw();
}

void PlayScene::finalize()
{
    // DeleteGraphなど
    field_->finalize();
    player_->finalize();

    // メモリ開放newした分
    delete field_;
    delete player_;
}