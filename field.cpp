#include "field.hpp"

bool Field::initialize( std::fstream& stage )
{
    texture_ = LoadGraph( "Texture/mario_field.png" );

    // ファイルポインタを先頭に移動
    stage.seekg( 0 );

    // 先頭8バイトをスキップ
    stage.seekg( 8L );

    stage.read( reinterpret_cast<char*>(&width_), sizeof( int ) );
    stage.read( reinterpret_cast<char*>(&height_), sizeof( int ) );

    // 20バイトスキップ
    stage.seekg( 20L );

    field_.resize( 2 );

    for( int layer = 0; layer < 2; layer++ )
    {
        for( int i = 0; i < height_; i++ )
        {
            field_[ layer ].push_back( std::vector<BlockBase*>( width_ ) );

            for( int j = 0; j < width_; j++ )
            {
                RECT rect;
                int position_x;
                int position_y;
                int id = 0;

                stage.read( reinterpret_cast<char*>(&id), sizeof( char ) );

                // Idに応じて登録

                if( id == kBrick )
                {
                    field_[ layer ][ i ][ j ] = new Brick;      // レンガの時
                }
                else if( id == kMystery )
                {
                    field_[ layer ][ i ][ j ] = new Mystery;    // はてなボックスの時
                }
                else
                {
                    field_[ layer ][ i ][ j ] = new BlockBase;  // ベースとなる箱
                }

                // 描画範囲を設定
                rect.top = id / kLength * kSize;
                rect.left = id % kLength * kSize;
                rect.bottom = kSize;
                rect.right = kSize;

                // 見えない空の部分の分だけ (-n*kSize)
                position_x = (kSize * j);
                position_y = (kSize * i) - kQuadruple;

                field_[ layer ][ i ][ j ]->initialize( id, rect, position_x, position_y );
            }
        }
    }

    return true;
}

void Field::update( PlayerData PlayerData )
{
  
    // 叩かれた右側
    if( PlayerData.break_right.x != 0 || PlayerData.break_right.y != 0 )
    {
        // 先に右の頭を登録
        block_right_.x = PlayerData.break_right.x;
        block_right_.y = PlayerData.break_right.y;

        field_[ 0 ][ PlayerData.break_right.y ][ PlayerData.break_right.x ]->standby( PlayerData.break_right.x, PlayerData.break_right.y );
    }

    // 叩かれた左側
    if( PlayerData.break_left.x != 0 || PlayerData.break_left.y != 0 )
    {
        block_left_.x = PlayerData.break_left.x;
        block_left_.y = PlayerData.break_left.y;

        field_[ 0 ][ PlayerData.break_left.y ][ PlayerData.break_left.x ]->standby( PlayerData.break_left.x, PlayerData.break_left.y );
    }

    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // 常に動ける準備はさせておく
            if( field_[ 0 ][ i ][ j ]->getId() == kBrick || field_[ 0 ][ i ][ j ]->getId() == kMystery || field_[ 0 ][ i ][ j ]->getId() == kNoblock )
            {
                // 更新されたBlockBase->update()を呼び出す
                field_[ 0 ][ i ][ j ]->update( PlayerData.player_status );
            }
        }
    }
}

void Field::draw( int ScreenOver )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // 裏背景の描画、縦、横を画像の切り取りに合わせて描画
            field_[ 0 ][ i ][ j ]->draw( texture_, ScreenOver );
        }
    }
}

void Field::drawFront( int ScreenOver )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // 裏背景の描画、縦、横を画像の切り取りに合わせて描画
            field_[ 1 ][ i ][ j ]->draw( texture_, ScreenOver );
        }
    }

}

void Field::finalize()
{
    // テクスチャ開放
    DeleteGraph( texture_ );

    // 三次元配列開放
    for( int layer = 0; layer < 2; layer++ )
    {
        for( int i = 0; i < height_; i++ )
        {
            for( int j = 0; j < width_; j++ )
            {
                SAFE_DELETE( field_[ layer ][ i ][ j ] );
            }
        }
    }
}

// 小さい体で当たったとき当たったブロックの関数を呼び出す
void Field::downBlock()
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            field_[ 0 ][ i ][ j ]->downBlock();
        }
    }
}

int Field::getId( int PosX, int PosY )
{
    // IDを計算して返す
    return field_[ 0 ][ PosY ][ PosX ]->getId();
}