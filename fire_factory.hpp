#include <Dxlib.h>
#include "collision.hpp"

class FireFactory :
    public Collision
{
public :
    const int kGravity = 1;
    const int kAnime = 8;
    const int kSpeed = 10;
    const int kJumpPower = 5;
    const int kGround = 575;

    FireFactory( Field* field ) : Collision( field ) {};
    void initialize( int, int, int );
    void update();
    void draw(int , const int );

    inline int getFirePosX() { return fire_pos_x_; }
    inline int getFirePosY() { return fire_pos_y_; }

private : 
    void animation();

    int texture_;               // �����Ŏ󂯎�����摜��ۑ�
    int direction_;             // �ŏ��Ɏ󂯎����������ۑ�

    int animation_cnt_;         // if������p
    int animation_;             // ���l�ɂ���ĉ�]����
    int fire_pos_x_;            // �����Ŏ󂯎����PosX��ۑ�
    int fire_pos_y_;            // �����Ŏ󂯎����PosY��ۑ�
};

// fire_factory�͍���鑤�Ȃ̂ŋ��ʂ����������������ށB
// ��j�Փ˔���A�`��֌W�A�A�j���[�V�������B