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
    static void update();                                 // ���݂̃V�[�����X�V����֐�
    static void draw();                                    // ���݂̃V�[����`�悷��֐�
    static void finalize();                                 // ���݂̃V�[������������֐�

private:
    static BaseScene* scene_;                       // ���݂̃V�[��
};