#pragma once 
#include "data_keeper.hpp"

class BaseScene
{
public:
    // â‘Î‚É–Y‚ê‚¿‚á‚¢‚¯‚È‚¢‚â‚Â
    virtual bool initialize() = 0;
    virtual void finalize() = 0;

    // Œ^–¼‡‚í‚¹‚Äg‚¤ ( ˆá‚¤‚ÆŒÄ‚Î‚ê‚È‚¢B)
    virtual void update() {};
    virtual void draw() {};
};