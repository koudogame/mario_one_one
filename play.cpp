#include "play.hpp"
#include "scene_manager.hpp"

PlayScene::PlayScene()
{
    // �N���X�|�C���^������
    field_ = nullptr;
}

PlayScene::~PlayScene()
{
}

bool PlayScene::initialize()
{
    // �C���X�^���X�̐���
    field_ = new Field();

    // �t�@�C���ɑ΂�����̓X�g���[��
    std::fstream stage;

    // ���͂̂��߂ɃI�[�v��������o�͂��o�C�i���ōs��
    stage.open( "mario.fmf", std::ios_base::in | std::ios_base::binary );

    // �N���X���̏��������s��
    field_->initialize( stage );

    return true;
}

void PlayScene::update()
{
    field_->update();
}

void PlayScene::draw()
{
    field_->draw(0/*������ScreenOver*/);
}

void PlayScene::finalize()
{
    // DeleteGraph�Ȃ�
    field_->finalize();

    // �������J��new������
    delete field_;
}