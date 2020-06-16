#include "play.hpp"
#include "scene_manager.hpp"

PlayScene::PlayScene()
{
    // �N���X�|�C���^������
    field_ = nullptr;
    player_ = nullptr;
}

PlayScene::~PlayScene()
{
}

bool PlayScene::initialize()
{
    // �C���X�^���X�̐���
    field_ = new Field();
    player_ = new Player();

    // �t�@�C���ɑ΂�����̓X�g���[��
    std::fstream stage;

    // ���͂̂��߂ɃI�[�v��������o�͂��o�C�i���ōs��
    stage.open( "mario.fmf", std::ios_base::in | std::ios_base::binary );

    // �N���X���̏��������s��
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
    field_->draw(0/*������ScreenOver*/);
    player_->draw();
}

void PlayScene::finalize()
{
    // DeleteGraph�Ȃ�
    field_->finalize();
    player_->finalize();

    // �������J��new������
    delete field_;
    delete player_;
}