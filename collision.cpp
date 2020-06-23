#include "collision.hpp"

Collision::Collision( Field* Field )
{
    field_ = Field;
}

int Collision::collision( RL Rl, BodyParts Parts )
{
    // Ž©•ª‚ª‚Ç‚±‚ÌId‚ÆG‚ê‚Ä‚¢‚é‚©‚ð•Ô‚·

    int x = body_[ Rl ][ Parts ][ 0 ] / 64;
    int y = body_[ Rl ][ Parts ][ 1 ] / 64;

    return field_->getId( x, y );
}
