#include <Dxlib.h>
#include "collision.hpp"

enum Rect
{
    kLeft, kTop, kRight, kBottom, kRect
};

class FireFactory :
    public Collision
{
public :
    const int kGravity     = 1;     // �d��
    const int kJumpPower   = 4;     // �W�����v��
    const int kDisplace    = 4;     // �����A�O����
    const int kControl     = 4;     // �z��`�撲���p
    const int kLimit       = 4;     // �A�j���؂�ւ�
    const int kSmall       = 6;     // ������
    const int kAnime       = 8;     // �A�j���[�V����
    const int kBic         = 12;    // �唚��
    const int kSpeed       = 12;    // �t�@�C�A�ړ����x
    const int kHalfSize    = 32;    // �u���b�N�����̑傫��
    const int kGroundArray = 14;    // �n�ʂɒl����z��ԍ�
    const int kSize        = 64;    // �u���b�N�T�C�Y
    const int kQuadruple   = 256;   // �u���b�N4�{�̑傫��
    const int kSextuple    = 384;   // �u���b�N6�{�̑傫��
    const int kSeptuple    = 448;   // �u���b�N7�{�̑傫��
    const int kGround      = 575;   // �n��

    const int kScreenXSize = 1280;  // X�����
    const int kScreenYSize = 720;   // Y�����

    FireFactory( Field* field ) : Collision( field ) {};
    void initialize( int, int, int );
    void update();
    void draw(int , const int );

    bool getCheckScreen(const int);    
    void animation();               // �A�j���[�V��������֐�
    void burnAnimation();           // �����A�j���[�V�����֐�
    void setFire(bool);         
    
    inline bool getExplode() { return explode_flag_; }

    inline int getFirePosX() { return fire_pos_x_; }
    inline int getFirePosY() { return fire_pos_y_; }


private : 
    bool side_touch_;               // �����瓖�����������ׂ�
    int texture_;                   // �����Ŏ󂯎�����摜��ۑ�
    int direction_;                 // �ŏ��Ɏ󂯎����������ۑ�

    int animation_cnt_;             // if������p
    int animation_;                 // ���l�ɂ���ĉ�]����
    int fire_pos_x_;                // �����Ŏ󂯎����PosX��ۑ�
    int fire_pos_y_;                // �����Ŏ󂯎����PosY��ۑ�

    int explosion_[ kRect ] = { 0 };    // ���j���oRect
    int explode_cnt_;
    int explode_flag_;
};

// fire_factory�͍���鑤�Ȃ̂ŋ��ʂ����������������ށB
// ��j�Փ˔���A�`��֌W�A�A�j���[�V�������B