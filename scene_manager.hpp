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

    static void ChangeScene( Scene scene );    // シーンを引数によって変える関数
    static void update();                                 // 現在のシーンを更新する関数
    static void draw();                                    // 現在のシーンを描画する関数
    static void finalize();                                 // 現在のシーンを消去する関数

private:
    static BaseScene* scene_;                       // 現在のシーン
};