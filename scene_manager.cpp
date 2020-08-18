#include "scene_manager.hpp"

// 新しいSceneを下に加える
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

// シーン更新
void SceneManager::draw()
{
    scene_->draw();
}

// シーン消去
void SceneManager::finalize()
{
    scene_->finalize();

    // 一番最後のシーン開放
    SAFE_DELETE( scene_);

}