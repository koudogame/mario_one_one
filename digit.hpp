#pragma once
    
inline int digit( int Number , uint32_t Digit )
{
    // �����ЂƂ����炷
    while( Digit >>= 1 )
        Number /= 10;

    // �w�肳�ꂽ����Ԃ�
    return Number % 10;
}