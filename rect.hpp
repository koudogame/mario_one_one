#pragma once

template <class T>
struct Rect {
    T left;   // SrcX
    T right;  // Width

    T top;    // SrcY
    T bottom; // Height
};