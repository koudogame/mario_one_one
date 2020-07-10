#include "result.hpp"
#include "scene_manager.hpp"

bool ResultScene::initialize()
{
    data_ = new DataKeeper();

    texture_ = LoadGraph( "Texture/ayaka.jpg" );

    push_time_go_ = 0;

    return false;
}

void ResultScene::update()
{
    if( !(GetJoypadInputState( DX_INPUT_PAD1 ) & PAD_INPUT_2) == 0 )
        push_time_go_++;
    else
        push_time_go_ = 0;

    if( push_time_go_ == 1 )
    {
        push_time_go_ = 0;
        SceneManager::ChangeScene( SceneManager::Scene::Play );
    }
}

void ResultScene::draw()
{
    DrawGraph( 0, 0,texture_, TRUE );

    int residue = data_->getResidue();
    int color = GetColor( 0, 0, 0 );
    DrawFormatString( 980, 240, color, "%d", residue );
}

void ResultScene::finalize()
{
    DeleteGraph( texture_ );
}