#include "scene_manager.hpp"

// 新しいSceneを下に加える
#include "title.hpp"
#include "tutorial.hpp"
#include "play.hpp"
#include "result.hpp"


// BaseSceneの初期化
BaseScene* SceneManager::scene_ = nullptr;

void SceneManager::ChangeScene( Scene scene )
{
    // もしシーンが選択されていたら消す
    if( scene_ != nullptr )
    {
        finalize();
    }

    // 帰ってきた引数でシーン切り替え
    switch( scene )
    {
    case Scene::Title:
        scene_ = new TitleScene();
        break;

    case Scene::Tutorial:
        scene_ = new TutorialScene();
        break;

    case Scene::Play:
        scene_ = new PlayScene();
        break;

    case Scene::Result:
        scene_ = new ResultScene();
        break;

        // 想定外を避ける
    default:
        break;
    }

    // 新しいシーンに遷移されたとき初期化
    scene_->initialize();
}

// シーン更新
void SceneManager::update()
{
    scene_->update();
}

// シーン消去
void SceneManager::finalize()
{
    scene_->finalize();

    // 一番最後のシーン開放
    delete scene_;

    // シーンを空にする
    scene_ = nullptr;
}