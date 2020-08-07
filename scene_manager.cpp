#include "scene_manager.hpp"

// �V����Scene�����ɉ�����
#include "play.hpp"
#include "result.hpp"


// BaseScene�̏�����
BaseScene* SceneManager::scene_ = nullptr;

void SceneManager::ChangeScene( Scene scene )
{
    // �����V�[�����I������Ă��������
    if( scene_ != nullptr )
    {
        finalize();
    }

    // �A���Ă��������ŃV�[���؂�ւ�
    switch( scene )
    {
    case Scene::Play:
        scene_ = new PlayScene();
        break;

    case Scene::Result:
        scene_ = new ResultScene();
        break;

        // �z��O�������
    default:
        break;
    }

    // �V�����V�[���ɑJ�ڂ��ꂽ�Ƃ�������
    scene_->initialize();
}

// �V�[���X�V
void SceneManager::update()
{
    scene_->update();
}

// �V�[���X�V
void SceneManager::draw()
{
    scene_->draw();
}

// �V�[������
void SceneManager::finalize()
{
    scene_->finalize();

    // ��ԍŌ�̃V�[���J��
    SAFE_DELETE( scene_);

}