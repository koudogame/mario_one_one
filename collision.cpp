#include "collision.hpp"

Collision::Collision( Field* Field )
{
    field_ = Field;
}

// �̗̂��T�C�h��o�^���t�B�[���h�̉��Ɠ������Ă��邩��Ԃ��֐�
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

// �̂̑�����o�^���A�t�B�[���h�̉��Ɠ������Ă��邩�Ԃ��֐�
int Collision::footColl()
{
    // return 1(Id <= 64),return 2(Id == 191), return 0 ���̑�

    int x1 = body_[ kRight ][ kFoot ][ kX ] / 64;
    int y1 = body_[ kRight ][ kFoot ][ kY ] / 64;

    int x2 = body_[ kLeft ][ kFoot ][ kX ] / 64;
    int y2 = body_[ kLeft ][ kFoot ][ kY ] / 64;

    // �����蔻��̂���u���b�N
    if( field_->getId( x1, y1 ) <= 64 || field_->getId( x2, y2 ) <= 64 )
         return 1;       
    // �󒆂ɕ����Ă���Ƃ�
    else if( field_->getId( x1, y1 ) == 191 || field_->getId( x2, y2 ) == 191 || 
             field_->getId( x1, y1 ) == 190 || field_->getId( x2, y2 ) == 190  )
        return 2;
    else
        return 0;
}

// �t�@�C�A�{�[����p�̏Փˏ���
int Collision::fireColl()
{
    // return 1(Id <= 64),return 2(Id == 191), return 0 ���̑�

    int x1 = body_[ kRight ][ kFoot ][ kX ] / 64;
    int y1 = body_[ kRight ][ kFoot ][ kY ] / 64;

    int x2 = body_[ kLeft ][ kFoot ][ kX ] / 64;
    int y2 = body_[ kLeft ][ kFoot ][ kY ] / 64;

    // �K�i�ɏՓ˂����Ƃ�
    if( field_->getId( x1, y1 ) == kStairs || field_->getId( x2, y2 ) == kStairs )
        return 3;
    // �����蔻��̂���u���b�N�ƏՓ˂����Ƃ�
    else if( field_->getId( x1, y1 ) <= 64 || field_->getId( x2, y2 ) <= 64 )
        return 1;
    // �󒆂ɕ����Ă���Ƃ�
    else if( field_->getId( x1, y1 ) == 191 || field_->getId( x2, y2 ) == 191 ||
        field_->getId( x1, y1 ) == 190 || field_->getId( x2, y2 ) == 190 )
        return 2;
    else
        return 0;
}

// �u���b�N��Id���擾����֐�
int Collision::collision( RL Rl, BodyParts Parts )
{
    // �������ǂ���Id�ƐG��Ă��邩��Ԃ�

    int x = body_[ Rl ][ Parts ][ 0 ] / 64;
    int y = body_[ Rl ][ Parts ][ 1 ] / 64;

    return field_->getId( x, y );
}