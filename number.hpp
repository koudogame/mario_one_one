#pragma once

// ���l�������rect.left���Ԃ��Ă���֐�
template <class T>
constexpr int left( T number )
{
    return number * 32;     // 32�͐����T�C�Y
};