#pragma once 

// �L�[���
enum Check
{
    kNothing = 0, kPress = 1, kHold = 2
};

class Xinput
{
public:
    // �{�^���̏�Ԃ��Ԃ��Ă���֐�
    static int XInput( uint32_t Button );

private:
    static int check_;
};