#pragma once

#include<DxLib.h>
#include"collision.hpp"

class FireBoll : 
    public Collision
{
public : 
    FireBoll( Field* field ) : Collision( field ) {};
    void initialize();
    void update(int, int, int, int); // position_x_, position_y_, status_, direction_;
    void draw();
    void finalize();

private : 
    int texture_;
    //std::vector<Fire*> fire_;
};