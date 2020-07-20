#include "field.hpp"

bool Field::initialize( std::fstream& stage )
{
    texture_ = LoadGraph( "Texture/mario_field.png" );

    block_rx_, block_ry_ = 0;
    block_lx_, block_ly_ = 0;

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
                rect.top = id / 16 * kSize;
                rect.left = id % 16 * kSize;
                rect.bottom = 64;
                rect.right = 64;

                // 見えない空の部分の分だけ (-n*64)
                position_x = (64 * j);
                position_y = (64 * i) - 256;

                field_[ layer ][ i ][ j ]->initialize( id, rect, position_x, position_y );
            }
        }
    }

    return true;
}

void Field::update( int Brx, int Bry, int Blx, int Bly, int Status )
{
    // 叩かれた右側
    if( Brx != 0 || Bry != 0 )
    {
        // 先に右の頭を登録
        block_rx_ = Brx;
        block_ry_ = Bry;

        field_[ 0 ][ Bry ][ Brx ]->standby(Brx, Bry);
    }

    // 叩かれた左側
    if( Blx != 0 || Bly != 0 )
    {
            block_lx_ = Blx;
            block_ly_ = Bly;

            field_[ 0 ][ Bly ][ Blx ]->standby(Blx, Bly);
    }

    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // 常に動ける準備はさせておく
            if( field_[ 0 ][ i ][ j ]->getId() == kBrick || field_[ 0 ][ i ][ j ]->getId() == kMystery || field_[ 0 ][ i ][ j ]->getId() == kNoblock )
            {
                // 更新されたBlockBase->update()を呼び出す
                field_[ 0 ][ i ][ j ]->update( Status );
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