#include "collision.hpp"

Collision::Collision( Field* Field )
{
    field_ = Field;
}

// 体の両サイドを登録しフィールドの何と当たっているかを返す関数
bool Collision::sideColl(RL rl)
{
    // 左右のIdが65以上ならtrue, 64以下ならfalse

    int x1 = body_[ rl ][ kShoulder ][ kX ] / 64;
    int y1 = body_[ rl ][ kShoulder ][ kY ] / 64;
                    
    int x2 = body_[ rl ][ kHands ][ kX ] / 64;
    int y2 = body_[ rl ][ kHands ][ kY ] / 64;

    if( field_->getId( x1, y1 ) > 64 && field_->getId( x2, y2 ) > 64 )
        return true;

    return false;       // Id <= 64
}

// 体の足元を登録し、フィールドの何と当たっているか返す関数
int Collision::footColl()
{
    // return 1(Id <= 64),return 2(Id == 191), return 0 その他

    int x1 = body_[ kRight ][ kFoot ][ kX ] / 64;
    int y1 = body_[ kRight ][ kFoot ][ kY ] / 64;

    int x2 = body_[ kLeft ][ kFoot ][ kX ] / 64;
    int y2 = body_[ kLeft ][ kFoot ][ kY ] / 64;

    // 当たり判定のあるブロック
    if( field_->getId( x1, y1 ) <= 64 || field_->getId( x2, y2 ) <= 64 )
         return 1;       
    // 空中に浮いているとき
    else if( field_->getId( x1, y1 ) == 191 || field_->getId( x2, y2 ) == 191 || 
             field_->getId( x1, y1 ) == 190 || field_->getId( x2, y2 ) == 190  )
        return 2;
    else
        return 0;
}

// ファイアボール専用の衝突処理
int Collision::fireColl()
{
    // return 1(Id <= 64),return 2(Id == 191), return 0 その他

    int x1 = body_[ kRight ][ kFoot ][ kX ] / 64;
    int y1 = body_[ kRight ][ kFoot ][ kY ] / 64;

    int x2 = body_[ kLeft ][ kFoot ][ kX ] / 64;
    int y2 = body_[ kLeft ][ kFoot ][ kY ] / 64;

    // 階段に衝突したとき
    if( field_->getId( x1, y1 ) == kStairs || field_->getId( x2, y2 ) == kStairs )
        return 3;
    // 当たり判定のあるブロックと衝突したとき
    else if( field_->getId( x1, y1 ) <= 64 || field_->getId( x2, y2 ) <= 64 )
        return 1;
    // 空中に浮いているとき
    else if( field_->getId( x1, y1 ) == 191 || field_->getId( x2, y2 ) == 191 ||
        field_->getId( x1, y1 ) == 190 || field_->getId( x2, y2 ) == 190 )
        return 2;
    else
        return 0;
}

// ブロックのIdを取得する関数
int Collision::collision( RL Rl, BodyParts Parts )
{
    // 自分がどこのIdと触れているかを返す

    int x = body_[ Rl ][ Parts ][ 0 ] / 64;
    int y = body_[ Rl ][ Parts ][ 1 ] / 64;

    return field_->getId( x, y );
}