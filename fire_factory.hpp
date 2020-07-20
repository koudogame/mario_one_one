#include <Dxlib.h>
#include "collision.hpp"

class FireFactory :
    public Collision
{
public :
    const int kGravity     = 1;
    const int kSmall       = 6;
    const int kBic         = 12;
    const int kAnime       = 8;
    const int kSpeed       = 12;
    const int kJumpPower   = 4;
    const int kGround      = 575;
    const int kScreenXSize = 1280;
    const int kScreenYSize = 720;

    FireFactory( Field* field ) : Collision( field ) {};
    void initialize( int, int, int );
    void update();
    void draw(int , const int );

    bool getCheckScreen(const int);    
    void animation();           // �A�j���[�V��������֐�
    void burnAnimation();       // �����A�j���[�V�����֐�
    void setFire(bool);         
    
    inline bool getExplode() { return explode_flag_; }

    inline int getFirePosX() { return fire_pos_x_; }
    inline int getFirePosY() { return fire_pos_y_; }


private : 
    bool side_touch_;           // �����瓖�����������ׂ�
    int texture_;               // �����Ŏ󂯎�����摜��ۑ�
    int direction_;             // �ŏ��Ɏ󂯎����������ۑ�

    int animation_cnt_;         // if������p
    int animation_;             // ���l�ɂ���ĉ�]����
    int fire_pos_x_;            // �����Ŏ󂯎����PosX��ۑ�
    int fire_pos_y_;            // �����Ŏ󂯎����PosY��ۑ�

    int explosion_[ 4 ] = { 0 };// ���j���oRect
    int explode_cnt_;
    int explode_flag_;
};

// fire_factory�͍���鑤�Ȃ̂ŋ��ʂ����������������ށB
// ��j�Փ˔���A�`��֌W�A�A�j���[�V�������B