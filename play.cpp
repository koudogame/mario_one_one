#include "play.hpp"
#include "scene_manager.hpp"

PlayScene::PlayScene()
{
    // クラスポインタ初期化
    field_ = nullptr;
}

PlayScene::~PlayScene()
{
}

bool PlayScene::initialize()
{
    // インスタンスの生成
    field_ = new Field();

    // ファイルに対する入力ストリーム
    std::fstream stage;

    // 入力のためにオープンする入出力をバイナリで行う
    stage.open( "mario.fmf", std::ios_base::in | std::ios_base::binary );

    // クラス内の初期化を行う
    field_->initialize( stage );

    return true;
}

void PlayScene::update()
{
    field_->update();
}

void PlayScene::draw()
{
    field_->draw(0/*ここにScreenOver*/);
}

void PlayScene::finalize()
{
    // DeleteGraphなど
    field_->finalize();

    // メモリ開放newした分
    delete field_;
}