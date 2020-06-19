#include "field.hpp"

static constexpr int kBlocksize = 64;

bool Field::initialize(std::fstream& stage)
{
    texture_ = LoadGraph("Texture/mario_field.png");

    // ファイルポインタを先頭に移動
    stage.seekg(0);

    // 先頭8バイトをスキップ
    stage.seekg(8L);

    stage.read(reinterpret_cast<char*>(&width_), sizeof(int));
    stage.read(reinterpret_cast<char*>(&height_), sizeof(int));

    // 20バイトスキップ
    stage.seekg(20L);

    field_.resize(2);

    for (int layer = 0; layer < 2; layer++)
    {
        for (int i = 0; i < height_; i++)
        {
            field_[layer].push_back(std::vector<BlockBase*>(width_));

            for (int j = 0; j < width_; j++)
            {
                RECT rect;
                int position_x;
                int position_y;
                int id = 0;

                stage.read(reinterpret_cast<char*>(&id), sizeof(char));

                if( id == kBrick )
                {
                    field_[ layer ][ i ][ j ] = new Brick;
                }
                else if( id == kMystery )
                {
                    field_[ layer ][ i ][ j ] = new Mystery;
                }
                else
                {
                    field_[ layer ][ i ][ j ] = new BlockBase;
                }

                // 描画範囲を設定
                rect.top = id / 16 * kBlocksize;
                rect.left = id % 16 * kBlocksize;
                rect.bottom = 64;
                rect.right = 64;

                // 見えない空の部分の分だけ (-n*64)
                position_x = (64 * j);
                position_y = (64 * i) - 256;

                field_[layer][i][j]->initialize(id, rect, position_x, position_y);
            }
        }
    }
    return true;
}

void Field::update( int Brx, int Bry, int Blx, int Bly )
{
    // 叩かれた右側のupdate()を呼ぶ
    if( Brx != 0 || Bry != 0 )
    {
        // 更新されたBlockBase->update()を呼び出す
        field_[ 1 ][ Bry ][ Brx ]->update();
    }

    // 叩かれた左側のupdate()を呼ぶ
    if( Blx != 0 || Bly != 0 )
    {
        // 更新されたBlockBase->update()を呼び出す
        field_[ 1 ][ Bly ][ Blx ]->update();
    }
    //for( int layer = 0; layer < 2; layer++ )
    //{
    //    for( int i = 0; i < height_; i++ )
    //    {
    //        for( int j = 0; j < width_; j++ )
    //        {
    //            // 裏背景の描画、縦、横を画像の切り取りに合わせて描画
    //            field_[ layer ][ i ][ j ]->update();
    //        }
    //    }
    //}
}

void Field::draw(int ScreenOver)
{
    for( int layer = 0; layer < 2; layer++ )
    {
        for( int i = 0; i < height_; i++ )
        {
            for( int j = 0; j < width_; j++ )
            {
                // 裏背景の描画、縦、横を画像の切り取りに合わせて描画
                field_[ layer ][ i ][ j ]->draw( texture_, ScreenOver );
            }
        }
    }
}


void Field::finalize()
{
    // テクスチャ開放
    DeleteGraph(texture_);

    // 三次元配列開放
    for (int layer = 0; layer < 2; layer++)
    {
        for (int i = 0; i < height_; i++)
        {
            for (int j = 0; j < width_; j++)
            {
                SAFE_DELETE(field_[layer][i][j]);
            }
        }
    }
}

int Field::getRightShoulderId( Side side_ )
{
    // 右肩のマップ番号
    int x = side_.right_shoulder_x / 64;
    int y = (side_.right_shoulder_y) / 64;

    // 右上のId
    return field_[ 1 ][ y ][ x ]->getId();
}

int Field::getRightHandId( Side side_ )
{
    // 右手のマップ番号
    int x = side_.right_hand_x / 64;
    int y = (side_.right_hand_y) / 64;

    // 右下のId
    return field_[ 1 ][ y ][ x ]->getId();
}

int Field::getLeftShoulderId( Side side_ )
{
    // 左肩のマップ番号
    int x = side_.left_shoulder_x / 64;
    int y = (side_.left_shoulder_y) / 64;

    // 右上のId
    return field_[ 1 ][ y ][ x ]->getId();
}

int Field::getLeftHandId( Side side_ )
{
    // 左手のマップ番号
    int x = side_.left_hand_x / 64;
    int y = (side_.left_hand_y) / 64;

    // 左下のId
    return field_[ 1 ][ y ][ x ]->getId();
}

int Field::getRightHeadId( UpDown updown_ )
{
    // 右頭のマップ番号
    int x = updown_.right_head_x / 64;
    int y = updown_.right_head_y / 64;

    // 右頭のId
    return field_[ 1 ][ y ][ x ]->getId();
}

int Field::getLeftHeadId( UpDown updown_ )
{
    // 左頭のマップ番号
    int x = updown_.left_head_x / 64;
    int y = updown_.left_head_y / 64;

    // 左頭のId
    return field_[ 1 ][ y ][ x ]->getId();
}

int Field::getRightFootId( UpDown updown_ )
{
    // 右足のマップ番号
    int x = updown_.right_foot_x / 64;
    int y = updown_.right_foot_y / 64;

    //int human[ kRL::kRLSize ][ kPartsSize ][ kXYSize ]
    //{
    //    kRight,kLeft,
    //    kFoot,kHead,kSholuder,kHand,
    //    kX,kY
    //};

    // 右足のId
    return field_[ 1 ][ y ][ x ]->getId();
}

int Field::getLeftFootId( UpDown updown_ )
{
    // 左足のマップ番号
    int x = updown_.left_foot_x / 64;
    int y = updown_.left_foot_y / 64;

    // 左足のId
    return field_[ 1 ][ y ][ x ]->getId();
}
