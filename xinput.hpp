#pragma once 

// �L�[���
enum Check
{
    kNothing = 0, kPress = 1, kHold = 2, kRelease = 3
};

class Xinput
{
public:
    // �{�^���̏�Ԃ��Ԃ��Ă���֐�
    static int xinput( uint32_t Button );

private:
    static int bit_;
    static int past_bit_;
};