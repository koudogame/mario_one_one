#pragma once 

class BaseScene
{
public:
    // ��΂ɖY�ꂿ�Ⴂ���Ȃ����
    virtual bool initialize() = 0;
    virtual void finalize() = 0;

    // �^�����킹�Ďg�� ( �Ⴄ�ƌĂ΂�Ȃ��B)
    virtual void update() {};
};