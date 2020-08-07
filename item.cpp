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
            
            // Idに応じて登録

            if( id == kMashroom )
                item_[ 0 ][ i ][ j ] = new Powerup( field_ );   // パワーアップアイテム
            else if( id == kFlag )
                item_[ 0 ][ i ][ j ] = new CastleFlag( field_ );// キャッスルフラッグ
            else if( id == kCoin )
                item_[ 0 ][ i ][ j ] = new Coin( field_ );      // コイン
            else if( id == kGoal )
                item_[ 0 ][ i ][ j ] = new Goal( field_ );      // ゴールフラッグ
            else
                item_[ 0 ][ i ][ j ] = new ItemBase(field_);

            // 描画範囲を設定
            rect.top = id / kLength * kSize;
            rect.left = id % kLength * kSize;
            rect.bottom = kSize;
            rect.right = kSize;

            // 見えない空の部分の分だけ (-n*kSize)
            position_x = (kSize * j);
            position_y = (kSize * i) - kQuadruple;

            item_[ 0 ][ i ][ j ]->initialize( id, rect, position_x, position_y );
        }
    }

    return true;
}

void Item::update( PlayerData PlayerData )
{
    // 常にupdate()は呼ばれる
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            item_[ 0 ][ i ][ j ]->update( PlayerData.scroll_cnt );
        }
    }

    // 叩かれた右側のflagChange()を呼ぶ
    if( PlayerData.break_right.x != 0 || PlayerData.break_right.y != 0 )
        item_[ 0 ][ PlayerData.break_right.y ][ PlayerData.break_right.x ]->flagChange( PlayerData.player_status );

    // コインの時追加
    coinCheckRight( PlayerData.break_right.x, PlayerData.break_right.y );

    // 叩かれた左側のflagChange()を呼ぶ
    if( PlayerData.break_left.x != 0 || PlayerData.break_left.y != 0 )
        item_[ 0 ][ PlayerData.break_left.y ][ PlayerData.break_left.x ]->flagChange( PlayerData.player_status );

    // コインの時追加
    coinCheckLeft( PlayerData.break_left.x, PlayerData.break_left.y );
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

void Item::coinCheckRight( int Brx, int Bry )
{
    // 連続して叩けないようにするために
    if( !(double_touch_.x == Brx && double_touch_.y == Bry ||
        past_r_.x == Brx && past_r_.y == Bry) )
    {
        // コインのIDの時
        if( item_[ 0 ][ Bry ][ Brx ]->getId() == kCoin )
        {
            // 叩いたか確認
            if( !item_[ 0 ][ Bry ][ Brx ]->getPunch() )
            {
                past_r_.x = Brx;
                past_r_.y = Bry;
                double_touch_.x = Brx;
                double_touch_.y = Bry;
                coin_counter_++;
            }
        }
    }
}


void Item::coinCheckLeft( int Blx, int Bly )
{
    // 連続して叩けないようにするために
    if( !(double_touch_.x == Blx && double_touch_.y == Bly ||
        past_l_.x == Blx && past_l_.y == Bly) )
    {
        // コインのIDの時
        if( item_[ 0 ][ Bly ][ Blx ]->getId() == kCoin )
        {
            // 叩いたか確認
            if( !item_[ 0 ][ Bly ][ Blx ]->getPunch() )
            {
                past_l_.x = Blx;
                past_l_.y = Bly;
                double_touch_.x = Blx;
                double_touch_.y = Bly;
                coin_counter_++;
            }
        }
    }
}

void Item::posCollision( int i, int j )
{
    item_[ 0 ][ i ][ j ]->posCollision();
}

void Item::getGoal( bool Goal )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            if( item_[ 0 ][ i ][ j ]->getId() == kGoal )
            item_[ 0 ][ i ][ j ]->getGoal( Goal );
        }
    }
}

void Item::getEnd( bool End )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            if( item_[ 0 ][ i ][ j ]->getId() == kFlag )
                item_[ 0 ][ i ][ j ]->upHata( End );
        }
    }
}

