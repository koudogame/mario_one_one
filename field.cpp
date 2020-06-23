#include "field.hpp"

constexpr int kBlocksize = 64;

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

    for( int i = 0; i < height_; i++ )
    {
        field_[ 0 ].push_back( std::vector<BlockBase*>( width_ ) );

        for( int j = 0; j < width_; j++ )
        {
            RECT rect;
            int position_x;
            int position_y;
            int id = 0;

            stage.read( reinterpret_cast<char*>(&id), sizeof( char ) );

            if( id == kBrick )
            {
                field_[ 0 ][ i ][ j ] = new Brick;
            }
            else if( id == kMystery )
            {
                field_[ 0 ][ i ][ j ] = new Mystery;
            }
            else
            {
                field_[ 0 ][ i ][ j ] = new BlockBase;
            }

            // 描画範囲を設定
            rect.top = id / 16 * kBlocksize;
            rect.left = id % 16 * kBlocksize;
            rect.bottom = 64;
            rect.right = 64;

            // 見えない空の部分の分だけ (-n*64)
            position_x = (64 * j);
            position_y = (64 * i) - 256;

            field_[ 0 ][ i ][ j ]->initialize( id, rect, position_x, position_y );
        }
    }

    return true;
}

void Field::update(int Brx, int Bry, int Blx, int Bly, int Status)
{
    // 叩かれた右側のupdate()を呼ぶ
    if( Brx != 0 || Bry != 0 )
    {
        // 更新されたBlockBase->update()を呼び出す
        field_[ 0 ][ Bry ][ Brx ]->update(Status);
    }

    // 叩かれた左側のupdate()を呼ぶ
    if( Blx != 0 || Bly != 0 )
    {
        // 更新されたBlockBase->update()を呼び出す
        field_[ 0 ][ Bly ][ Blx ]->update(Status);
    }
}

void Field::draw(int ScreenOver)
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

void Field::finalize()
{
    // テクスチャ開放
    DeleteGraph( texture_ );

    // 三次元配列開放
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            SAFE_DELETE( field_[ 0 ][ i ][ j ] );
        }
    }
}

int Field::getId( int PosX, int PosY )
{
    // IDを計算して返す
    return field_[ 0 ][ PosY ][ PosX ]->getId();
}