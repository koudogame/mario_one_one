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

void Field::setPosition(RL rl, BodyParts parts, Position position, int Movement)
{
    // ポジションをセット
    bodyId_[rl][parts][position] = Movement;
}

int Field::getPoint(RL rl, BodyParts parts)
{
    // セットしたIDを計算してゲット
    int x = bodyId_[rl][parts][0] / 64;
    int y = bodyId_[rl][parts][1] / 64;

    // IDを計算して返す
    return field_[1][y][x]->getId();
}