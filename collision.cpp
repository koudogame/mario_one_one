#include "collision.hpp"

Collision::Collision( Field* Field )
{
    field_ = Field;
}

bool Collision::sideColl(RL rl)
{
    // ¶‰E‚ÌId‚ª65ˆÈã‚È‚çtrue, 64ˆÈ‰º‚È‚çfalse

    int x1 = body_[ rl ][ kShoulder ][ kX ] / 64;
    int y1 = body_[ rl ][ kShoulder ][ kY ] / 64;
                    
    int x2 = body_[ rl ][ kHands ][ kX ] / 64;
    int y2 = body_[ rl ][ kHands ][ kY ] / 64;

    if( field_->getId( x1, y1 ) > 64 && field_->getId( x2, y2 ) > 64 )
        return true;

    return false;       // Id <= 64
}

int Collision::footColl()
{
    // return 1(Id <= 64),return 2(Id == 191), return 0 ‚»‚Ì‘¼

    int x1 = body_[ kRight ][ kFoot ][ kX ] / 64;
    int y1 = body_[ kRight ][ kFoot ][ kY ] / 64;

    int x2 = body_[ kLeft ][ kFoot ][ kX ] / 64;
    int y2 = body_[ kLeft ][ kFoot ][ kY ] / 64;

    if( field_->getId( x1, y1 ) <= 64 || field_->getId( x2, y2 ) <= 64 )
        return 1;       
    else if( field_->getId( x1, y1 ) == 191 || field_->getId( x2, y2 ) == 191 )
        return 2;
    else
        return 0;
}

int Collision::collision( RL Rl, BodyParts Parts )
{
    // Ž©•ª‚ª‚Ç‚±‚ÌId‚ÆG‚ê‚Ä‚¢‚é‚©‚ð•Ô‚·

    int x = body_[ Rl ][ Parts ][ 0 ] / 64;
    int y = body_[ Rl ][ Parts ][ 1 ] / 64;

    return field_->getId( x, y );
}

void Collision::setMarioPos( int PosX, int PosY )
{
    mario_pos_x_ = PosX;
    mario_pos_y_ = PosY;
}

void Collision::setItemPos( int PosX, int PosY )
{
    item_pos_x_ = PosX;
    item_pos_y_ = PosY + (kSize * 4);
}

bool Collision::getCollision(int Status)
{
    int mx1 = mario_pos_x_;
    int my1 = mario_pos_y_;

    int mx2 = mario_pos_x_ + kSize;
    int my2 = mario_pos_y_ + kSize;

    int ex1 = item_pos_x_;
    int ey1 = item_pos_y_;

    int ex2 = item_pos_x_ + kSize;
    int ey2 = item_pos_y_ + kSize;

    if(!(mx1 <= ex2 || ex1 <= mx2 || my1 <= ey2 || ey1 <= my2))
        return false;

    return true;
}
