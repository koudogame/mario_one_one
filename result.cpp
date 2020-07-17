#include "result.hpp"
#include "scene_manager.hpp"

bool ResultScene::initialize()
{
    return false;
}

void ResultScene::update()
{
    SceneManager::ChangeScene( SceneManager::Scene::Play );
}

void ResultScene::draw()
{
}

void ResultScene::finalize()
{
}