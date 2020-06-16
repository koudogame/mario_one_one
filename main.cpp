#include <DxLib.h>
#include "scene_manager.hpp"

// WinMain関数
int WINAPI WinMain( HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC )
{
    ChangeWindowMode( TRUE );               // ウィンドウモード切り替え
    SetGraphMode( 1280, 720, 32 );           // ウィンドウサイズ変更
    SetBackgroundColor( 100, 149, 237 );   // 背景色変更（はる推奨カラー）
    if( DxLib_Init() == -1 )    return -1;       // Dxlib初期化

    SetDrawScreen( DX_SCREEN_BACK );  // 裏画面描画に設定
    
    /*initialize関数*/
    SceneManager::ChangeScene(SceneManager::Scene::Play);

    // ここからメインループ
    // ずっと更新が必要なものをここに記入していく
    while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {        
        ClearDrawScreen();                            // 画面消去                       

        /*update関数*/
        SceneManager::update();

        /* draw関数 */
        SceneManager::draw();

        ScreenFlip();                                      // 画面切り替え
    }

    /*finalize関数*/
    SceneManager::finalize();

    DxLib_End();                                         // DXライブラリ終了処理

    return 0;
}