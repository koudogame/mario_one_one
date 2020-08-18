#pragma once

// �\����
struct PlayerData
{
    Position<int> break_right;      // �@�����E�����W
    Position<int> break_left;       // �@�����������W

    Position<int> player_position;  // Player��ʍ��W
    Position<int> total_position;   // Player���v���W
    
    int player_status;              // Player���
    int push_squat;                 // ���Ⴊ�݉����Ă��鎞��
    int scroll_cnt;                 // ��ʂ���������
    int direction;                  // �����Ă������

    bool end_flag;                  // true : ���O        , false : ����
    bool goal_flag;                 // true : �S�[���O    , false : �S�[����
    bool gameover_flag;             // true : ���S�O      , false : ���S��
    bool invincible_flag;           // true : ���G����Ȃ�, false : ���G
};