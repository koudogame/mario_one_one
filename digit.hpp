#pragma once
    
inline int digit( int Number , uint32_t Digit )
{
    // 桁をひとつずつずらす
    while( Digit >>= 1 )
        Number /= 10;

    // 指定された桁を返す
    return Number % 10;
}