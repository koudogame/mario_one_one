#include "ui_time.hpp"

void UITime::initialize()
{
    time_limit_ = true;             // ���ԓ��O�`�B�p
    goal_flag_ = true;              // �v���C���[�S�[�����

    clock_cnt_ = 0;                 // �J�E���g������
    timer_ = kDefaultTimer;         // timer�Z�b�g
}

void UITime::update()
{
    // ���Ԑ����O && �S�[���O
    if( time_limit_ && goal_flag_ )
    {
        clock_cnt_++;               // ���ԊǗ�

        if( clock_cnt_ == kSecond )
        {
            clock_cnt_ = 0;         // �J�E���g���Z�b�g

            if( timer_ > 0 )
                timer_--;           // ���Ԃ����炷
            else
                time_limit_ = false;
        }

        // �w��񐔕��V�t�g
        auto binary = 0b100;
        for( int i = 0; i < kDigitArray; i++ )
        {
            digit_[ i ] = digit( timer_, binary >> i );
        }
    }
}

void UITime::draw( int Texture )
{
    // �p�ӂ��ꂽ���܂ŕ`��
    for( int i = 0; i < kDigitArray; i++ )
    {
        DrawRectGraph( kStartPos + (i * kQuarterSize), kUIposY,
            left( digit_[ i ] ), rect_.top, rect_.right, rect_.bottom,
            Texture, TRUE, FALSE );
    }
}

void UITime::setGoalFlag(bool GoalFlag)
{
    goal_flag_ = GoalFlag;          // �t���O�̎󂯓n��
}

void UITime::setTime( int Time )
{
    timer_ = Time;

    // �w��񐔕��V�t�g
    auto binary = 0b100;
    for( int i = 0; i < kDigitArray; i++ )
    {
        digit_[ i ] = digit( timer_, binary >> i );
    }
}
