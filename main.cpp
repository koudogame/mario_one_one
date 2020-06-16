#include <DxLib.h>
#include "scene_manager.hpp"

// WinMain�֐�
int WINAPI WinMain( HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC )
{
    ChangeWindowMode( TRUE );               // �E�B���h�E���[�h�؂�ւ�
    SetGraphMode( 1280, 720, 32 );           // �E�B���h�E�T�C�Y�ύX
    SetBackgroundColor( 100, 149, 237 );   // �w�i�F�ύX�i�͂鐄���J���[�j
    if( DxLib_Init() == -1 )    return -1;       // Dxlib������

    SetDrawScreen( DX_SCREEN_BACK );  // ����ʕ`��ɐݒ�
    
    /*initialize�֐�*/
    SceneManager::ChangeScene(SceneManager::Scene::Play);

    // �������烁�C�����[�v
    // �����ƍX�V���K�v�Ȃ��̂������ɋL�����Ă���
    while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {        
        ClearDrawScreen();                            // ��ʏ���                       

        /*update�֐�*/
        SceneManager::update();

        /* draw�֐� */
        SceneManager::draw();

        ScreenFlip();                                      // ��ʐ؂�ւ�
    }

    /*finalize�֐�*/
    SceneManager::finalize();

    DxLib_End();                                         // DX���C�u�����I������

    return 0;
}