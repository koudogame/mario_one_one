#include "share.hpp"
#include "ui_manager.hpp"

void UIManager::initialize()
{
    // �摜�ǂݍ���
    texture_ = LoadGraph( "texture/number.png" );  

    // �e��UI������
    map_.initialize();
    coin_.initialize();
    time_.initialize();
    score_.initialize();
}

void UIManager::update( bool GoalFlag )
{    
    // �S�[����Ԏ擾
    time_.setGoalFlag( GoalFlag );

    // �e��UI�X�V
    map_.update();
    coin_.update();
    time_.update();
    score_.update();
}

void UIManager::draw()
{
    // �e��UI�`��
    map_.draw( texture_ );
    coin_.draw( texture_ );
    time_.draw( texture_ );
    score_.draw( texture_ );
}

void UIManager::finalize()
{
    // �摜�j��
    DeleteGraph( texture_ );

    // �e��UI�j��
    map_.finalize();
    coin_.finalize();
    time_.finalize();
    score_.finalize();
}

void UIManager::timeScore()
{
    // ���Ԃ��P���炵�X�R�A��50���₷
    score_.changeTime(time_.getTime());

    // ���炵�����l��Ԃ�
    time_.setTime( score_.getTime() );
}

void UIManager::coinCheck( int Coin )
{
    // �R�C���̃J�E���g�A�b�v�֐�
    coin_.coinCounter( Coin );
}