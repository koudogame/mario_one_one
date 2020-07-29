#include "ui_time.hpp"

void UITime::initialize()
{
    time_limit_ = true;         // ���ԓ��O�`�B�p
    goal_flag_ = true;          // �v���C���[�S�[�����

    number_c_ = 0;              // �O���ڏ�����
    clock_cnt_ = 0;             // �J�E���g������
    timer_ = kDefaultTimer;     // timer�Z�b�g

    // �S����
    rect_.right = kQuarterSize;
    rect_.top = 0;
    rect_.bottom = kQuarterSize;
}

void UITime::update()
{
    if( time_limit_ && goal_flag_ ) 
    {
        clock_cnt_++;               // ���ԊǗ�

        if( clock_cnt_ == kSecond )
        {
            clock_cnt_ = 0;         // �J�E���g���Z�b�g
            
            if( timer_ > 0 )
                timer_--;               // ���Ԃ����炷
            else
                time_limit_ = false;
        }

        // �������Ԍv�Z    
        number_c_ = timer_ / 100;           // �O����
        number_b_ = (timer_ % 100) / 10;    // �񌅖�
        number_a_ = timer_ % 10;            // �ꌅ��
    }
}

void UITime::draw(int Texture)
{
    // �ꌅ��
    DrawRectGraph( kNumPosAX, kUIposY,
        left( number_a_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
    
    // �񌅖�
    DrawRectGraph( kNumPosBX, kUIposY,
        left( number_b_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );
    
    // �O����
    DrawRectGraph( kNumPosCX, kUIposY,
        left( number_c_ ), rect_.top, rect_.right, rect_.bottom,
        Texture, TRUE, FALSE );

}

void UITime::setGoalFlag(bool GoalFlag)
{
    goal_flag_ = GoalFlag;
}
