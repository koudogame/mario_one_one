#include "item.hpp"


Item::Item( Field* Field )
{
    field_ = Field;
}

bool Item::initialize( std::fstream& stage )
{
    texture_ = LoadGraph( "texture/mario_item.png" );

    // ファイルポインタを先頭に移動
    stage.seekg( 0 );

    // 先頭8バイトをスキップ
    stage.seekg( 8L );

    stage.read( reinterpret_cast<char*>(&width_), sizeof( int ) );
    stage.read( reinterpret_cast<char*>(&height_), sizeof( int ) );

    // 20バイトスキップ
    stage.seekg( 20L );

    item_.resize( 2 );

    for( int i = 0; i < height_; i++ )
    {
        item_[ 0 ].push_back( std::vector<ItemBase*>( width_ ) );

        for( int j = 0; j < width_; j++ )
        {
            RECT rect;
            int position_x;
            int position_y;
            int id = 0;

            stage.read( reinterpret_cast<char*>(&id), sizeof( char ) );
            
            if( id == kPowerup )
                item_[ 0 ][ i ][ j ] = new Powerup( field_ );
            else if( id == kCoin )
                item_[ 0 ][ i ][ j ] = new Coin(field_);
            else
                item_[ 0 ][ i ][ j ] = new ItemBase(field_);

            // 描画範囲を設定
            rect.top = id / 16 * kItemsize;
            rect.left = id % 16 * kItemsize;
            rect.bottom = 64;
            rect.right = 64;

            // 見えない空の部分の分だけ (-n*64)
            position_x = (64 * j);
            position_y = (64 * i) - 256;

            item_[ 0 ][ i ][ j ]->initialize( id, rect, position_x, position_y );
        }
    }

    return true;
}

void Item::update( int Brx, int Bry, int Blx, int Bly, int Status, int Screenover )
{
    // 常にupdate()は呼ばれる
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            item_[ 0 ][ i ][ j ]->update(Screenover);
        }
    }

    // 叩かれた左側のflagChange()を呼ぶ
    if( Blx != 0 || Bly != 0 )
    {
        item_[ 0 ][ Bly ][ Blx ]->flagChange( Status );
    }

    if( Brx != 0 || Bry != 0 )
    {
        item_[ 0 ][ Bry ][ Brx ]->flagChange( Status );
    }
}

void Item::draw( int Screenover )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // 裏背景の描画、縦、横を画像の切り取りに合わせて描画
            item_[ 0 ][ i ][ j ]->draw( texture_, Screenover );
        }
    }
}

void Item::finalize()
{
    // テクスチャ開放
    DeleteGraph( texture_ );

    // 三次元配列開放
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            SAFE_DELETE( item_[ 0 ][ i ][ j ] );
        }
    }
}
