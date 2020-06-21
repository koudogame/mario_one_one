#include "field.hpp"

static constexpr int kBlocksize = 64;

bool Field::initialize(std::fstream& stage)
{
    texture_ = LoadGraph("Texture/mario_field.png");

    // �t�@�C���|�C���^��擪�Ɉړ�
    stage.seekg(0);

    // �擪8�o�C�g���X�L�b�v
    stage.seekg(8L);

    stage.read(reinterpret_cast<char*>(&width_), sizeof(int));
    stage.read(reinterpret_cast<char*>(&height_), sizeof(int));

    // 20�o�C�g�X�L�b�v
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

                // �`��͈͂�ݒ�
                rect.top = id / 16 * kBlocksize;
                rect.left = id % 16 * kBlocksize;
                rect.bottom = 64;
                rect.right = 64;

                // �����Ȃ���̕����̕����� (-n*64)
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
    // �@���ꂽ�E����update()���Ă�
    if( Brx != 0 || Bry != 0 )
    {
        // �X�V���ꂽBlockBase->update()���Ăяo��
        field_[ 1 ][ Bry ][ Brx ]->update();
    }

    // �@���ꂽ������update()���Ă�
    if( Blx != 0 || Bly != 0 )
    {
        // �X�V���ꂽBlockBase->update()���Ăяo��
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
                // ���w�i�̕`��A�c�A�����摜�̐؂���ɍ��킹�ĕ`��
                field_[ layer ][ i ][ j ]->draw( texture_, ScreenOver );
            }
        }
    }
}


void Field::finalize()
{
    // �e�N�X�`���J��
    DeleteGraph(texture_);

    // �O�����z��J��
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
    // �|�W�V�������Z�b�g
    bodyId_[rl][parts][position] = Movement;
}

int Field::getPoint(RL rl, BodyParts parts)
{
    // �Z�b�g����ID���v�Z���ăQ�b�g
    int x = bodyId_[rl][parts][0] / 64;
    int y = bodyId_[rl][parts][1] / 64;

    // ID���v�Z���ĕԂ�
    return field_[1][y][x]->getId();
}