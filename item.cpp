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

            if( id == kPowerup )
                item_[ 0 ][ i ][ j ] = new Powerup( field_ );   // �p���[�A�b�v�A�C�e��
            else if( id == kFlag )
                item_[ 0 ][ i ][ j ] = new CastleFlag( field_ );      // �L���b�X���t���b�O
            else if( id == kCoin )
                item_[ 0 ][ i ][ j ] = new Coin( field_ );      // �R�C��
            else if( id == kGoal )
                item_[ 0 ][ i ][ j ] = new Goal( field_ );      // �S�[���t���b�O
            else
                item_[ 0 ][ i ][ j ] = new ItemBase(field_);

            // �`��͈͂�ݒ�
            rect.top = id / 16 * kItemsize;
            rect.left = id % 16 * kItemsize;
            rect.bottom = 64;
            rect.right = 64;

            // �����Ȃ���̕����̕����� (-n*64)
            position_x = (64 * j);
            position_y = (64 * i) - 256;

            item_[ 0 ][ i ][ j ]->initialize( id, rect, position_x, position_y );
        }
    }

    return true;
}

void Item::update( int Brx, int Bry, int Blx, int Bly, int Status, int Screenover )
{
    // ���update()�͌Ă΂��
    for( int i = 0; i < height_; i++ )
    {
        for( int j = 0; j < width_; j++ )
        {
            item_[ 0 ][ i ][ j ]->update(Screenover);
        }
    }

    // �@���ꂽ������flagChange()���Ă�
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

