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
    player_ = new Player(field_);

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
    player_->update();
    field_->update( player_->getBreakRightX(), player_->getBreakRightY(),
        player_->getBreakLeftX(), player_->getBreakLeftY() );
}

void PlayScene::draw()
{
    field_->draw(player_->getScrollCnt());
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