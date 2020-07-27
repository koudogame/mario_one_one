#include "pos_collision.hpp"
    
// ��`�Ƌ�`�̓����蔻��
bool PosCollision::getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y )
{
    int mario_left = Mario_x;
    int mario_right = Mario_x + kSize;

    int mario_top = Mario_y;
    int mario_bottom = Mario_y + kSize;

    int other_left = Other_x;
    int other_right = Other_x + kSize;

    int other_top = Other_y;
    int other_bottom = Other_y + kSize;

    // 4�{�̎��̔���
    if( (mario_right > other_left) && (other_right > mario_left)
        && (mario_bottom > other_top) && (other_bottom > mario_top) )
    {
        // �Փ˂��Ă��܂�
        return false;
    }

    // �Փ˂��Ă��܂���
    return true;
}

// �t�@�C�A�ƓG�̏Փ˔���
bool PosCollision::getFireEnemyCollision( int Fire_x, int Fire_y, int Enemy_x, int Enemy_y)
{
    int fire_left    = Fire_x;
    int fire_right   = Fire_x + kHalfSize;

    int fire_top     = Fire_y + kQuadruple;
    int fire_bottom  = Fire_y + kHalfSize + kQuadruple;

    int enemy_left   = Enemy_x;
    int enemy_right  = Enemy_x + kSize;

    int enemy_top    = Enemy_y;
    int enemy_bottom = Enemy_y + kSize;

    // 4�{�̎��̔���
    if( (fire_right > enemy_left) && (enemy_right > fire_left)
    && (fire_bottom > enemy_top) && (enemy_bottom > fire_top) )
    {
        // �Փ˂��Ă��܂�
        return false;
    }

    // �Փ˂��Ă��܂���
    return true;
}


// �}���I�ƓG�̏Փ˔���
int PosCollision::getEnemyCollision( int Mario_x, int Mario_y, int Enemy_x, int Enemy_y, int Status )
{
    int enemy_x1 = Enemy_x;
    int enemy_x2 = Enemy_x + kSize;

    int enemy_y1 = Enemy_y;
    int enemy_y2 = Enemy_y + kSize;


    // �����̓o�^
    body_[ kRight ][ kFoot ][ kX ] = (Mario_x + (kSize - kGather));
    body_[ kLeft ][ kFoot ][ kX ] = (Mario_x + kGather);

    // �������Ƃ����傫���Ƃ���
    if( Status == 0 )
    {
        body_[ kRight ][ kFoot ][ kY ] = (Mario_y + kSize + 1);             // �ЂƂ�̑傫��
        body_[ kLeft ][ kFoot ][ kY ] = (Mario_y + kSize + 1);              // �ЂƂ�̑傫��
    }
    else
    {
        body_[ kRight ][ kFoot ][ kY ] = (Mario_y + kDoubleSize + 1);       // �ЂƂ�̑傫��
        body_[ kLeft ][ kFoot ][ kY ] = (Mario_y + kDoubleSize + 1);        // �ЂƂ�̑傫��
    }


    // �E�̂̓o�^
    body_[ kRight ][ kShoulder ][ kX ] = (Mario_x + kSize + 1);             // �ЂƂ�̑傫��
    body_[ kRight ][ kShoulder ][ kY ] = (Mario_y + kGather);
    body_[ kRight ][ kHands ][ kX ] = (Mario_x + kSize + 1);                // �ЂƂ�̑傫��

    // �������Ƃ����傫���Ƃ���
    if( Status == 0 )
        body_[ kRight ][ kHands ][ kY ] = (Mario_y + kSize - kGather);
    else
        body_[ kRight ][ kHands ][ kY ] = (Mario_y + kDoubleSize - kGather);



    // ���̂̓o�^
    body_[ kLeft ][ kShoulder ][ kX ] = (Mario_x - 1);                      // �ЂƂ�̑傫��
    body_[ kLeft ][ kShoulder ][ kY ] = (Mario_y + kGather);
    body_[ kLeft ][ kHands ][ kX ]    = (Mario_x - 1);                      // �ЂƂ�̑傫��

    // �������Ƃ����傫���Ƃ���
    if( Status == 0 )
        body_[ kLeft ][ kHands ][ kY ] = (Mario_y + kSize - kGather);
    else
        body_[ kLeft ][ kHands ][ kY ] = (Mario_y + kDoubleSize - kGather);



    // �����G�Ɠ������Ă���
    if( enemy_x1 <= body_[ kRight ][ kFoot ][ kX ] && body_[ kRight ][ kFoot ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kRight ][ kFoot ][ kY ] && body_[ kRight ][ kFoot ][ kY ] <= enemy_y2 ||
        enemy_x1 <= body_[ kLeft ][ kFoot ][ kX ] && body_[ kLeft ][ kFoot ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kLeft ][ kFoot ][ kY ] && body_[ kLeft ][ kFoot ][ kY ] <= enemy_y2 )
        return 1;   


    // �E�̂��G�Ɠ������Ă���
    else if(
        enemy_x1 <= body_[ kRight ][ kShoulder ][ kX ] && body_[ kRight ][ kShoulder ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kRight ][ kShoulder ][ kY ] && body_[ kRight ][ kShoulder ][ kY ] <= enemy_y2 ||
        enemy_x1 <= body_[ kRight ][ kHands ][ kX ] && body_[ kRight ][ kHands ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kRight ][ kHands ][ kY ] && body_[ kRight ][ kHands ][ kY ] <= enemy_y2 )
        return 2;       
    

    // ���̂��G�Ɠ������Ă���
    else if(
        enemy_x1 <= body_[ kLeft ][ kShoulder ][ kX ] && body_[ kLeft ][ kShoulder ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kLeft ][ kShoulder ][ kY ] && body_[ kLeft ][ kShoulder ][ kY ] <= enemy_y2 ||
        enemy_x1 <= body_[ kLeft ][ kHands ][ kX ] && body_[ kLeft ][ kHands ][ kX ] <= enemy_x2 &&
        enemy_y1 <= body_[ kLeft ][ kHands ][ kY ] && body_[ kLeft ][ kHands ][ kY ] <= enemy_y2 )
        return 3;       


    return 0;
}
