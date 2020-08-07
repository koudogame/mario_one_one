#include "item.hpp"


Item::Item( Field* Field )
{
    field_ = Field;
}

bool Item::initialize( std::fstream& stage )
{
    texture_ = LoadGraph( "texture/mario_item.png" );

    // �t�@�C���|�C���^��擪�Ɉړ�
    stage.seekg( 0 );

    // �擪8�o�C�g���X�L�b�v
    stage.seekg( 8L );

    stage.read( reinterpret_cast<char*>(&width_), sizeof( int ) );
    stage.read( reinterpret_cast<char*>(&height_), sizeof( int ) );

    // 20�o�C�g�X�L�b�v
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
            
            // Id�ɉ����ēo�^

            if( id == kMashroom )
                item_[ 0 ][ i ][ j ] = new Powerup( field_ );   // �p���[�A�b�v�A�C�e��
            else if( id == kFlag )
                item_[ 0 ][ i ][ j ] = new CastleFlag( field_ );// �L���b�X���t���b�O
            else if( id == kCoin )
                item_[ 0 ][ i ][ j ] = new Coin( field_ );      // �R�C��
            else if( id == kGoal )
                item_[ 0 ][ i ][ j ] = new Goal( field_ );      // �S�[���t���b�O
            else
                item_[ 0 ][ i ][ j ] = new ItemBase(field_);

            // �`��͈͂�ݒ�
            rect.top = id / kLength * kSize;
            rect.left = id % kLength * kSize;
            rect.bottom = kSize;
            rect.right = kSize;

            // �����Ȃ���̕����̕����� (-n*kSize)
            position_x = (kSize * j);
            position_y = (kSize * i) - kQuadruple;

            item_[ 0 ][ i ][ j ]->initialize( id, rect, position_x, position_y );
        }
    }

    return true;
}

void Item::update( PlayerData PlayerData )
{
    // ���update()�͌Ă΂��
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            item_[ 0 ][ i ][ j ]->update( PlayerData.scroll_cnt );
        }
    }

    // �@���ꂽ�E����flagChange()���Ă�
    if( PlayerData.break_right.x != 0 || PlayerData.break_right.y != 0 )
        item_[ 0 ][ PlayerData.break_right.y ][ PlayerData.break_right.x ]->flagChange( PlayerData.player_status );

    // �R�C���̎��ǉ�
    coinCheckRight( PlayerData.break_right.x, PlayerData.break_right.y );

    // �@���ꂽ������flagChange()���Ă�
    if( PlayerData.break_left.x != 0 || PlayerData.break_left.y != 0 )
        item_[ 0 ][ PlayerData.break_left.y ][ PlayerData.break_left.x ]->flagChange( PlayerData.player_status );

    // �R�C���̎��ǉ�
    coinCheckLeft( PlayerData.break_left.x, PlayerData.break_left.y );
}

void Item::draw( int Screenover )
{
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            // ���w�i�̕`��A�c�A�����摜�̐؂���ɍ��킹�ĕ`��
            item_[ 0 ][ i ][ j ]->draw( texture_, Screenover );
        }
    }
}

void Item::finalize()
{
    // �e�N�X�`���J��
    DeleteGraph( texture_ );

    // �O�����z��J��
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
    // �A�����Ē@���Ȃ��悤�ɂ��邽�߂�
    if( !(double_touch_.x == Brx && double_touch_.y == Bry ||
        past_r_.x == Brx && past_r_.y == Bry) )
    {
        // �R�C����ID�̎�
        if( item_[ 0 ][ Bry ][ Brx ]->getId() == kCoin )
        {
            // �@�������m�F
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
    // �A�����Ē@���Ȃ��悤�ɂ��邽�߂�
    if( !(double_touch_.x == Blx && double_touch_.y == Bly ||
        past_l_.x == Blx && past_l_.y == Bly) )
    {
        // �R�C����ID�̎�
        if( item_[ 0 ][ Bly ][ Blx ]->getId() == kCoin )
        {
            // �@�������m�F
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

