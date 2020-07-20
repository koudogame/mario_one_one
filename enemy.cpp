#include "enemy.hpp"

Enemy::Enemy( Field* Field )
{
    field_ = Field;
}

void Enemy::initalize( std::fstream& FieldEnemy )
{
    texture_ = LoadGraph( "texture/mario_enemy.png" );

    // ファイルポインタを先頭に移動
    FieldEnemy.seekg( 0 );

    // 先頭バイトをスキップ
    FieldEnemy.seekg(8L);

    FieldEnemy.read( reinterpret_cast<char*>(&width_), sizeof( int ) );
    FieldEnemy.read( reinterpret_cast<char*>(&height_), sizeof( int ) );

    // 20バイトスキップ
    FieldEnemy.seekg( 20L );

    enemy_.resize( 2 );

    for( int i = 0; i < height_; i++ )
    {
        enemy_[ 0 ].push_back( std::vector<EnemyBase*>( width_ ) );

        for( int j = 0; j < width_; j++ )
        {
            RECT rect;
            int position_x;
            int position_y;
            int id = 0;

            FieldEnemy.read( reinterpret_cast<char*>(&id), sizeof( char ) );

            // 各配列に情報をnewする

            if( id == kKuribo )
                enemy_[ 0 ][ i ][ j ] = new Kuribo( field_ );   // クリボー
            else if( id == kTurtle )
                enemy_[ 0 ][ i ][ j ] = new Turtle( field_ );   // ノコノコ
            else
                enemy_[ 0 ][ i ][ j ] = new EnemyBase( field_ );// ベース


            // 描画範囲を設定
            rect.top = id / 16 * kSize;
            rect.left = id % 16 * kSize;
            rect.bottom = kSize;
            rect.right = kSize;

            // 見えない空の部分の分だけ (-n*64)
            position_x = (kSize * j);
            position_y = (kSize * i) - (kSize * 4);

            enemy_[ 0 ][ i ][ j ]->initialize( id, rect, position_x, position_y );
        }
    }
}

void Enemy::update( int ScreenOver )
{  
    // 常にupdate()は呼ばれる
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // 渡したScreenOverで移動するかを判定させる
            enemy_[ 0 ][ i ][ j ]->update( ScreenOver );
        }
    }
}

void Enemy::draw( int ScreenOver )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // 裏背景の描画、縦、横を画像の切り取りに合わせて描画
            enemy_[ 0 ][ i ][ j ]->draw( texture_, ScreenOver );
        }
    }
}

void Enemy::finalize()
{
    // テクスチャ開放
    DeleteGraph( texture_ );

    // 三次元配列開放
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            SAFE_DELETE( enemy_[ 0 ][ i ][ j ] );
        }
    }
}

// ポジション情報がマリオと当たったときに呼ばれる関数
void Enemy::posCollision( int i, int j, int Touch )
{
    enemy_[ 0 ][ i ][ j ]->posCollision(Touch);
}

// 甲羅状態で衝突したときに呼ばれる関数
void Enemy::shellCollision( int i, int j )
{
    enemy_[ 0 ][ i ][ j ]->shellCollision();
}

// ファイアボールと衝突したときに呼ばれる関数
void Enemy::fireCollision( int i, int j )
{
    enemy_[ 0 ][ i ][ j ]->fireCollision();
}

// ポジションがぶつかり向きを変更するときに呼ばれる関数
void Enemy::changeDirection( int i, int j )
{
    enemy_[ 0 ][ i ][ j ]->changeDirection();
}
