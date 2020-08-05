#include "collision.hpp"

class FireFactory :
    public Collision
{
public :
    const int kJumpPower   = 8;     // �W�����v��
    const int kLimit       = 4;     // �A�j���؂�ւ�
    const int kAnime       = 8;     // �A�j���[�V����
    const int kSpeed       = 16;    // �t�@�C�A�ړ����x
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

    inline int getFirePosX() { return fire_position_.x; }
    inline int getFirePosY() { return fire_position_.y; }


private : 
    Rect<int> rect_;                // Rect��p��
    Position<int> fire_position_;   // Position��p�� 

    bool side_touch_;               // �����瓖�����������ׂ�
    int texture_;                   // �����Ŏ󂯎�����摜��ۑ�
    int direction_;                 // �ŏ��Ɏ󂯎����������ۑ�

    int animation_cnt_;             // if������p
    int animation_;                 // ���l�ɂ���ĉ�]����

    int explode_cnt_;
    int explode_flag_;
};

// fire_factory�͍���鑤�Ȃ̂ŋ��ʂ����������������ށB
// ��j�Փ˔���A�`��֌W�A�A�j���[�V�������B