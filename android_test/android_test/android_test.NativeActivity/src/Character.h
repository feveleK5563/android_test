#pragma once
#include "Math.h"
#include "Counter.hpp"
#include "ImageDrawer.h"

//�L�����N�^�[(������)�̓���ƕ`��Ǘ��N���X
//�ڐG���Ă���u���b�N�ɉ����ē�������ʓ��������ŊǗ�����
class Character
{
private:
    Math::Vec2 pos_;            //���W
    Math::Box2D land_rect_;     //�n�`����p��`
    float velocity_;            //�ړ����x
    bool is_vel_constant_;      //�ړ����x�����ɂ���t���O
    Counter<float> grav_cnt_;   //�d�͉��Z
    bool is_gravity_;           //�d�͗L���t���O
    Math::BoxCP box_cp_;        //�`���ʒu

public:
    Character();

    void NomalMove(const Math::Vec2& direction);            //�߂荞�ݓ��̕␳���s��Ȃ��ړ�����
    void NoSinkMove(const Math::Vec2& direction);           //�߂荞�܂Ȃ��ړ�����
    void AutoRevitionMove(const Math::Vec2& direction);     //�߂荞�݂Ȃ� + ���������@�\�t���ړ�����

    void SetBoxCP(Math::BoxCP cp);                  //�`���ʒu��ݒ�
    void SetPos(const Math::Vec2& pos);             //���W��ݒ�
    void SetLandRect(const Math::Box2D& land_rect); //��`��ݒ�
    void SetVelocity(const float velocity);         //�ړ����x��ݒ�
    void SetIsVelConstant(bool is_vel_constant);    //�ړ����x�����ɂ���t���O�̐ݒ�
    void SetIsGravity(bool is_gravity);             //�d�͗L���t���O�̐ݒ�

    const Math::Vec2& GetPos() const;                       //���W���擾
    Math::Vec2 GetCenterPos() const;                        //�n�`����p��`�̒��S���W���擾
    Math::Vec2 GetPosForCam(bool isCenter = false) const;   //�J���������̍��W���擾
    Math::Box2D GetLandRect() const;        //�n�`����p��`���擾
    const float& GetVelocity() const;       //�ړ����x���擾
    bool IsGravity() const;                 //�d�͗L���t���O���擾
    bool IsGround() const;                  //�n�ʂƐڐG���Ă��邩�擾

    //��`��`��
    void DrawRect(bool is_fill, int color = 0xffffff, bool for_cam = false) const;

private:
    Math::Vec2 GetVec(const Math::Vec2& direction); //���Z����ړ��ʂ��擾(�d�͌v�Z���s��)
    Math::Vec2 GetAddGravityVec();                  //���Z����d�͗ʂ��擾
};