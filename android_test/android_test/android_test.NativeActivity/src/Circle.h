#pragma once
#include <memory>
#include <string>
#include "DxLib.h"
#include "Math.h"
#include "ImageDrawer.h"
#include "Counter.hpp"

//�V�F�[�_�[�ɑ�����
struct CircleInfo
{
    FLOAT2 window_size; //��ʃT�C�Y
    FLOAT2 center_pos;  //���S���W
    float radius;       //���a
    bool color_flag;    //���F�t���O
    float   r;
    float   g;
    float   b;
    float   a;
};

//----------------------------------------------
//�V�F�[�_�[�g���̂ł��̊Ǘ�
class CResource
{
private:
    static std::weak_ptr<CResource> instance_;

public:
    std::string shader_name;
    std::string buffer_name;

    CResource();    //�R���X�g���N�^
    ~CResource();   //�f�X�g���N�^
    static std::shared_ptr<CResource> Create(); //���\�[�X�̐���
};

//----------------------------------------------
//�C����G��ŕ`�悳�������Ǘ�����N���X
class Circle
{
private:
    FLOAT2 window_size_; //��ʃT�C�Y
    float radius_;       //���a
    bool color_flag_;    //���F�t���O

    std::shared_ptr<CResource> cres_;
    Counter<float> counter_;

public:
    Circle(float spread_speed);

    //�X�V
    void Update();

    //�`��
    void Draw(const Math::Vec2& pos, const Color& color);

    //���F�t���O�ݒ�
    void SetColorFlag(bool color_flag);
};