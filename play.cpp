#include "play.hpp"
#include "scene_manager.hpp"

PlayScene::PlayScene()
{
    // クラスポインタ初期化
    gf_      = nullptr;
    ui_      = nullptr;
    bm_      = nullptr;
    item_    = nullptr;
    enemy_   = nullptr;
    field_   = nullptr;
    player_  = nullptr;
    pos_col_ = nullptr;
}

PlayScene::~PlayScene()
{
}

bool PlayScene::initialize()
{
    // インスタンスの生成
    field_   = new Field();   
    item_    = new Item( field_ );
    enemy_   = new Enemy( field_ );
    player_  = new Player( field_ );
    bm_      = new BallManagement( field_ );
    pos_col_ = new PosCollision(); 
    ui_      = new UIManager();
    gf_      = new GoalFire();

    // ファイルに対する入力ストリーム
    std::fstream stage;
    std::fstream item;
    std::fstream enemy;

    // 入力のためにオープンする入出力をバイナリで行う
    stage.open( "mario_field2.fmf", std::ios_base::in | std::ios_base::binary );
    enemy.open( "mario_enemy.fmf", std::ios_base::in | std::ios_base::binary );
    item.open( "mario_item.fmf", std::ios_base::in | std::ios_base::binary );

    // クラス内の初期化を行う
    item_->initialize( item );
    enemy_->initalize( enemy );
    field_->initialize( stage );
    bm_->initialize();
    player_->initialize();
    ui_->initialize();
    gf_->initialize();

    gf_flag_ = true;
    touch_ = 0;
    clear_num_ = 0;
    change_timer_ = 0;
 
    return true;
}

void PlayScene::update()
{
    player_->update( ui_->timeLimit() );

    // マリオ透明かつ拡縮時 時を止めるｂd
    if( player_->getInvincibleTime() )
    {
        field_->downBlock();

        field_->update( player_->getBreakRightX(), player_->getBreakRightY(),
            player_->getBreakLeftX(), player_->getBreakLeftY(), player_->getStatus() );

        item_->update( player_->getBreakRightX(), player_->getBreakRightY(),
            player_->getBreakLeftX(), player_->getBreakLeftY(), player_->getStatus(), player_->getScrollCnt() );

        item_->getGoal( player_->getGoal() );

        enemy_->update( player_->getScrollCnt() );

        bm_->update( player_->getPositionX(), player_->getPositionY(),
            player_->getStatus(), player_->getDirection(), player_->getGoal(), player_->getPosY(), player_->getPushSquat() );

        ui_->coinCheck( item_->getCoin() );

        ui_->update( player_->getGoal() );

        bm_->posCheck( player_->getScrollCnt() );           // 重くならないように画面外は判定しない処理
        bm_->sideCheck();                                   // 横から当たったら消去

        // ゲームオーバーではないとき
        if( player_->getGameover() )
        {
            // 敵と敵の当たり判定を取る
            for( int i = 0; i < enemy_->getHeight(); i++ )
            {
                for( int j = 0; j < enemy_->getWidth(); j++ )
                {
                    // クリボー、ノコノコ以外のときスキップ
                    if( enemy_->getId( i, j ) != kKuribo && enemy_->getId( i, j ) != kTurtle )
                        continue;


                    for( int k = 0; k < enemy_->getHeight(); k++ )
                    {
                        for( int l = 0; l < enemy_->getWidth(); l++ )
                        {
                            // クリボー、ノコノコ以外のときスキップ
                            if( enemy_->getId( k, l ) != kKuribo && enemy_->getId( k, l ) != kTurtle )
                                continue;

                            // 同じ数値の時は判定しない
                            if( i == k && j == l )
                                continue;


                            // 敵Aと敵Bの判定を取る
                            if( pos_col_->getCollision(
                                enemy_->getEnemyPosX( i, j ), enemy_->getEnemyPosY( i, j ),
                                enemy_->getEnemyPosX( k, l ), enemy_->getEnemyPosY( k, l ) ) == false )
                            {
                                // 衝突しているとき
                                // それぞれを反対方向に歩ませる
                                enemy_->changeDirection( i, j );
                            }
                        }
                    }
                }
            }

            // get関数を呼んで結果を返す(enemy & enemy)
            for( int i = 0; i < enemy_->getHeight(); i++ )
            {
                for( int j = 0; j < enemy_->getWidth(); j++ )
                {
                    for( int k = 0; k < bm_->getSize(); k++ )
                    {
                        // すべての炎と敵の衝突を確認
                        if( pos_col_->getFireEnemyCollision( bm_->getFirePosX( k ), bm_->getFirePosY( k ),
                            enemy_->getEnemyPosX( i, j ), enemy_->getEnemyPosY( i, j ) ) == false )
                        {
                            // 炎、敵用に新たな関数を用意する
                            bm_->enemyCollision( k );
                            enemy_->fireCollision( i, j );
                        }
                    }
                }
            }

            // get関数を呼んで数値を渡す（Item）
            for( int i = 0; i < item_->getHeight(); i++ )
            {
                for( int j = 0; j < item_->getWidth(); j++ )
                {
                    // アイテムとマリオの衝突判定を調べる
                    if( pos_col_->getCollision( player_->getPositionX(), player_->getPositionY(),
                        item_->getItemPosX( i, j ), item_->getItemPosY( i, j ) ) == false )
                    {
                        int id = item_->getId( i, j );

                        // 当たり判定を取りたいIdだけ衝突を確かめる
                        if( id == kMashroom || id == kFlower )
                        {
                            player_->itemCollision();
                            item_->posCollision( i, j );
                        }
                    }
                }
            }

            // get関数を呼んで数値を渡す（Enemy）
            for( int i = 0; i < enemy_->getHeight(); i++ )
            {
                for( int j = 0; j < enemy_->getWidth(); j++ )
                {
                    // 上から踏みつけたとき
                    if( pos_col_->getEnemyCollision(
                        player_->getPositionX(), player_->getPositionY(),
                        enemy_->getEnemyPosX( i, j ), enemy_->getEnemyPosY( i, j ),
                        player_->getStatus() ) == 1 )
                    {
                        int id = enemy_->getId( i, j );
                        touch_ = 1;

                        if( id == kKuribo || id == kTurtle )
                        {
                            // 踏まれた後の演出
                            player_->enemyStepon();
                            enemy_->posCollision( i, j, touch_ );
                        }

                        // 上から甲羅踏みつけたとき
                        if( id == kShell )
                        {
                            // 踏まれた後の演出
                            player_->enemyStepon();
                            enemy_->shellCollision( i, j );
                        }
                    }
                    // 体の右と衝突したとき
                    else if( pos_col_->getEnemyCollision(
                        player_->getPositionX(), player_->getPositionY(),
                        enemy_->getEnemyPosX( i, j ), enemy_->getEnemyPosY( i, j ),
                        player_->getStatus() ) == 2 )
                    {
                        int id = enemy_->getId( i, j );
                        touch_ = 2;

                        if( id == kShell )
                        {
                            // 甲羅が動いているか
                            if( enemy_->getPushFlag( i, j ) )
                                enemy_->posCollision( i, j, touch_ );
                            else
                            {
                                // 無敵時間中は当たり判定を取らない
                                if( player_->getInvincible() )
                                    player_->enemyCollision();
                            }
                        }

                        if( id == kKuribo || id == kTurtle )
                        {
                            // 無敵時間中は当たり判定を取らない
                            if( player_->getInvincible() == true )
                                player_->enemyCollision();
                        }

                    }
                    // 体の左と衝突したとき
                    else if( pos_col_->getEnemyCollision(
                        player_->getPositionX(),
                        player_->getPositionY(),
                        enemy_->getEnemyPosX( i, j ),
                        enemy_->getEnemyPosY( i, j ),
                        player_->getStatus() ) == 3 )
                    {
                        int id = enemy_->getId( i, j );
                        touch_ = 3;

                        if( id == kShell )
                        {
                            // 甲羅が動いているか
                            if( enemy_->getPushFlag( i, j ) )
                                enemy_->posCollision( i, j, touch_ );
                            else
                            {
                                // 無敵時間中は当たり判定を取らない
                                if( player_->getInvincible() )
                                    player_->enemyCollision();
                            }
                        }

                        if( id == kKuribo || id == kTurtle )
                        {
                            // 無敵時間中は当たり判定を取らない
                            if( player_->getInvincible() )
                                player_->enemyCollision();
                        }
                    }
                }
            }

            // 透明化前(一桁を取得)
            if( player_->getEnd() )
            {
                clear_num_ = ui_->getTime() % 10;
                gf_flag_ = gf_->numCheck( clear_num_ );
            }
            // 透明化後
            else
            {
                // 0になるまでスコア加算
                if( ui_->getTime() != 0 )
                    // UI内で関数をまわす
                    ui_->timeScore(); 
                else
                {
                    // スコア加算後に旗を掲げる
                    item_->getEnd( player_->getEnd() );

                    // １桁が1,3,6の時
                    if( !gf_flag_ )
                    {

                        // numCheckが0以外の時
                        if( gf_->getNumber() != 0 )
                            gf_->createFire();

                        if( !gf_->getSceneFlag() )
                            resultScene();
                    }
                    else
                        resultScene();
                }
            }
        }
        else
            // ゲームオーバー数秒後シーンチェンジ
            resultScene();
    }
}

void PlayScene::draw()
{       
    field_->drawFront(player_->getScrollCnt());     // フィールド背景
    item_->draw(player_->getScrollCnt());           // アイテム
    field_->draw( player_->getScrollCnt() );        // 触れるブロック
    enemy_->draw(player_->getScrollCnt());          // 敵
    bm_->draw( player_->getScrollCnt() );           // ファイアボール
    player_->draw();                                // マリオ
    ui_->draw();                                    // UI
    gf_->draw();                                    // 花火
}

void PlayScene::finalize()
{
    // DeleteGraphなど
    field_->finalize();
    item_->finalize();
    enemy_->finalize();
    bm_->finalize();
    player_->finalize();
    ui_->finalize();
    gf_->finalize();

    // メモリ開放newした分
    delete gf_;
    delete ui_;
    delete bm_;
    delete item_;
    delete field_;
    delete enemy_;
    delete player_;
    delete pos_col_;
}

void PlayScene::resultScene()
{
    change_timer_++;

    if( change_timer_ > kChangeTime )
        SceneManager::ChangeScene( SceneManager::Scene::Result );
}