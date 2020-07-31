#include "xinput.hpp"

int Xinput::xinput( uint32_t Button )
{
    // ���ׂẴr�b�g��ԕۑ�
    bit_ = GetJoypadInputState( DX_INPUT_PAD1 );

    // �ߋ�OFF = 0, �ߋ�ON = 1;
    int past_check = past_bit_ & Button;

    // ��OFF = 0, ��ON = 1;
    int now_check = bit_ & Button;

    // �ߋ�OFF, ��ON
    if( past_check == 0 )
    {
        past_bit_ = bit_;
        return kPress;
    }

    // �ߋ�ON, ��ON
    if( past_check == 1 )
    {
        past_bit_ = bit_;
        return kHold;
    }

    // �ߋ�ON, ��OFF
    if( past_check == 1 && now_check == 0 )
    {
        past_bit_ = bit_;
        return kRelease;
    }

    // ���̑�
    past_bit_ = bit_;
    return kNothing;
}

int Xinput::bit_ = 0;      // �N���X�ϐ���`
int Xinput::past_bit_ = 0; // �N���X�ϐ���`