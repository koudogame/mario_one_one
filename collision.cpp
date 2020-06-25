#include "collision.hpp"
int Collision::mario_pos_x_;                                 // �}���I�|�W�V����
int Collision::mario_pos_y_;
int Collision::item_pos_x_;                                  // �A�C�e���|�W�V����
int Collision::item_pos_y_;

Collision::Collision( Field* Field )
{
    field_ = Field;
}

bool Collision::sideColl(RL rl)
{
    // ���E��Id��65�ȏ�Ȃ�true, 64�ȉ��Ȃ�false

    int x1 = body_[ rl ][ kShoulder ][ kX ] / 64;
    int y1 = body_[ rl ][ kShoulder ][ kY ] / 64;
                    
    int x2 = body_[ rl ][ kHands ][ kX ] / 64;
    int y2 = body_[ rl ][ kHands ][ kY ] / 64;

    if( field_->getId( x1, y1 ) > 64 && field_->getId( x2, y2 ) > 64 )
        return true;

    return false;       // Id <= 64
}

int Collision::footColl()
{
    // return 1(Id <= 64),return 2(Id == 191), return 0 ���̑�

    int x1 = body_[ kRight ][ kFoot ][ kX ] / 64;
    int y1 = body_[ kRight ][ kFoot ][ kY ] / 64;

    int x2 = body_[ kLeft ][ kFoot ][ kX ] / 64;
    int y2 = body_[ kLeft ][ kFoot ][ kY ] / 64;

    if( field_->getId( x1, y1 ) <= 64 || field_->getId( x2, y2 ) <= 64 )
        return 1;       
    else if( field_->getId( x1, y1 ) == 191 || field_->getId( x2, y2 ) == 191 )
        return 2;
    else
        return 0;
}

int Collision::collision( RL Rl, BodyParts Parts )
{
    // �������ǂ���Id�ƐG��Ă��邩��Ԃ�

    int x = body_[ Rl ][ Parts ][ 0 ] / 64;
    int y = body_[ Rl ][ Parts ][ 1 ] / 64;

    return field_->getId( x, y );
}

void Collision::setMarioPos( int PosX, int PosY )
{
    mario_pos_x_ = PosX;
    mario_pos_y_ = PosY;
}

void Collision::setItemPos( int PosX, int PosY )
{
    item_pos_x_ = PosX;
    item_pos_y_ = PosY;
}

bool Collision::getCollision()
{
    // ��`�Ƌ�`�̓����蔻��
    {
        int mario_left = mario_pos_x_;
        int mario_right = mario_pos_x_ + kSize;

        int mario_top = mario_pos_y_;
        int mario_bottom = mario_pos_y_ + kSize;

        int item_left = item_pos_x_;
        int item_right = item_pos_x_ + kSize;

        int item_top = item_pos_y_;
        int item_bottom = item_pos_y_ + kSize;

        // 4�{�̎��̔���
        if( (mario_right > item_left) && (item_right > mario_left)
            && (mario_bottom > item_top) && (item_bottom > mario_top) )
        {
            // �Փ˂��Ă��܂�
            return false;
        }

        // �Փ˂��Ă��܂���
        return true;
    }
}


