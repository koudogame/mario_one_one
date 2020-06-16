#include "field.hpp"

static constexpr int kBlocksize = 64;

bool Field::initialize(std::fstream& stage)
{
    texture_ = LoadGraph("Texture/mario1.png");

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

                //if (id == )
                //{
                field_[layer][i][j] = new BlockBase;
                //}

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

void Field::update()
{
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
