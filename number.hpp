#pragma once

// 数値を入れるとrect.leftが返ってくる関数
template <class T>
constexpr int left( T number )
{
    return number * 16;     // 16は数字サイズ
};