#pragma once

// 数値を入れるとrect.leftが返ってくる関数
template <class T>
constexpr int left( T number )
{
    return number * 32;     // 32は数字サイズ
};