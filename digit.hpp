#pragma once
    
inline int digit( int Number , uint32_t Digit )
{
    // Œ…‚ð‚Ð‚Æ‚Â‚¸‚Â‚¸‚ç‚·
    while( Digit >>= 1 )
        Number /= 10;

    // Žw’è‚³‚ê‚½Œ…‚ð•Ô‚·
    return Number % 10;
}