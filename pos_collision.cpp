#include "pos_collision.hpp"

bool PosCollision::getCollision( int Mario_x, int Mario_y, int Other_x, int Other_y )
{
    // ‹éŒ`‚Æ‹éŒ`‚Ì“–‚½‚è”»’è
    {
        int mario_left = Mario_x;
        int mario_right = Mario_x + kSize;

        int mario_top = Mario_y;
        int mario_bottom = Mario_y + kSize;

        int other_left = Other_x;
        int other_right = Other_x + kSize;
           
        int other_top = Other_y;
        int other_bottom = Other_y + kSize;

        // 4–{‚Ì²‚Ì”»’è
        if( (mario_right > other_left) && (other_right > mario_left)
            && (mario_bottom > other_top) && (other_bottom > mario_top) )
        {
            // Õ“Ë‚µ‚Ä‚¢‚Ü‚·
            return false;
        }

        // Õ“Ë‚µ‚Ä‚¢‚Ü‚¹‚ñ
        return true;
    }
}