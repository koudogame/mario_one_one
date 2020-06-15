#pragma once 
#include "base_scene.hpp"

class SceneManager
{
public:
    enum Scene
    {
        Title,
        Tutorial,
        Play,
        Result
    };

    static void ChangeScene( Scene scene );    // �V�[���������ɂ���ĕς���֐�
    static void finalize();                                 // ���݂̃V�[������������֐�
    static void update();                                 // ���݂̃V�[�����X�V����֐�

private:
    static BaseScene* scene_;                       // ���݂̃V�[��
};