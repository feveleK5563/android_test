#include "TaskDefData.h"
#include "Character.h"
#include "Task_Map.h"
#include "Task_Camera.h"
#include "ImageLoader.h"

Character::Character():
    velocity_(0.f),
    is_vel_constant_(false),
    grav_cnt_(Physic::gravity),
    is_gravity_(false),
    box_cp_(Math::BoxCP::TOP_LEFT) {}

//-----------------------------------------------------------------------------
//�߂荞�ݓ��̕␳���s��Ȃ��ړ�����
void Character::NomalMove(const Math::Vec2& direction)
{
    Math::Vec2 vec(GetVec(direction));

    if (vec == Math::Vec2(0.f, 0.f))
    {
        //�ړ����Ȃ��Ȃ牽�����Ȃ�
        return;
    }

    pos_ += vec;
}

//-----------------------------------------------------------------------------
//�߂荞�܂Ȃ��ړ�����
void Character::NoSinkMove(const Math::Vec2& direction)
{
    Math::Vec2 vec(GetVec(direction));

    if (vec == Math::Vec2(0.f, 0.f))
    {
        //�ړ����Ȃ��Ȃ牽�����Ȃ�
        return;
    }

    //�߂荞�܂Ȃ��ړ�����
    auto map = TaskSystem::GetTaskOne<Map::Task>(Map::def_task);
    for (int xy = 0; xy < 2; ++xy)
    {
        Math::Vec2 add;
        while (vec(xy) != 0.f)
        {
            if (vec(xy) > 1.f) { add(xy) = 1.f; vec(xy) -= 1.f; }
            else if (vec(xy) < -1.f) { add(xy) = -1.f; vec(xy) += 1.f; }
            else { add(xy) = vec(xy); vec(xy) = 0.f; }

            if (map->GetHitBlockTrait(land_rect_.GetOffset(pos_ + add, box_cp_))
                != Map::BlockTrait::Non)
            {
                break;
            }
            pos_(xy) += add(xy);
        }
    }

    if (map->IsHitFoot(land_rect_.GetOffset(pos_, box_cp_)))
    {
        grav_cnt_.Reset();
    }
}

//-----------------------------------------------------------------------------
//�߂荞�݂Ȃ� + ���������@�\�t���ړ�����
void Character::AutoRevitionMove(const Math::Vec2& direction)
{
    if (direction == Math::Vec2(0.f, 0.f))
    {
        //�ړ����Ȃ��Ȃ�߂荞�݂Ȃ��ړ������s��
        NoSinkMove(direction);
        return;
    }

    Math::Vec2 cder(direction);

    auto map = TaskSystem::GetTaskOne<Map::Task>(Map::def_task);
    //��`���ӂ̐ڐG�ʒu���擾���A���̈ʒu�ɂ���Ĉړ�������ϊ�����
    switch (map->GetHitRectGirth(land_rect_.GetOffset(pos_, box_cp_), Map::BlockTrait::Nomal))
    {
    case Map::RectGirth::U_LEFT:    //��̍�
        if (-0.2f < cder.x && cder.x < 0.2f)
            cder.x = 1.f;   //�E�����֕ϊ�
        break;

    case Map::RectGirth::U_RIGHT:   //��̉E
        if (-0.2f < cder.x && cder.x < 0.2f)
            cder.x = -1.f;  //�������֕ϊ�
        break;

    case Map::RectGirth::L_UP:      //���E�̏�
    case Map::RectGirth::R_UP:
        if (-0.2f < cder.y && cder.y < 0.2f)
            cder.y = 1.f;   //�������֕ϊ�
        break;

    case Map::RectGirth::L_DOWN:    //���E�̉�
    case Map::RectGirth::R_DOWN:
        if (-0.2f < cder.y && cder.y < 0.2f)
            cder.y = -1.f;  //������֕ϊ�
        break;
    }

    NoSinkMove(cder);
}

//-----------------------------------------------------------------------------
//�`���ʒu��ݒ�
void Character::SetBoxCP(Math::BoxCP cp)
{
    box_cp_ = cp;
}

//-----------------------------------------------------------------------------
//���W��ݒ�
void Character::SetPos(const Math::Vec2& pos)
{
    pos_ = pos;
}

//-----------------------------------------------------------------------------
//��`��ݒ�
void Character::SetLandRect(const Math::Box2D& land_rect)
{
    land_rect_ = land_rect;
}

//-----------------------------------------------------------------------------
//�ړ����x��ݒ�
void Character::SetVelocity(float velocity)
{
    velocity_ = velocity;
}

//-----------------------------------------------------------------------------
//�ړ����x�������~���͈͂ɕ␳����t���O��ݒ�
void Character::SetIsVelConstant(bool is_vel_constant)
{
    is_vel_constant_ = is_vel_constant;
}

//-----------------------------------------------------------------------------
//�d�͗L���t���O�̐ݒ�
void Character::SetIsGravity(bool is_gravity)
{
    is_gravity_ = is_gravity;
    if (!is_gravity_)
    {
        grav_cnt_.Reset();
    }
}


//-----------------------------------------------------------------------------
//���W���擾
const Math::Vec2& Character::GetPos() const
{
    return pos_;
}
//-----------------------------------------------------------------------------
//�n�`����p��`�̒��S���W���擾
Math::Vec2 Character::GetCenterPos() const
{
    Math::Vec2 ul = land_rect_.GetOffset(pos_, box_cp_).GetPos();
    ul.x += land_rect_.w / 2.f;
    ul.y += land_rect_.h / 2.f;
    return ul;
}
//-----------------------------------------------------------------------------
//�J���������̍��W���擾
Math::Vec2 Character::GetPosForCam(bool isCenter) const
{
    auto cam = TaskSystem::GetTaskOne<Camera::Task>(Camera::def_task);
    if (isCenter)
    {
        return cam->GetScreenPos(GetCenterPos());
    }
    return cam->GetScreenPos(pos_);
}

//-----------------------------------------------------------------------------
//�n�`����p��`���擾
Math::Box2D Character::GetLandRect() const
{
    return land_rect_.GetOffset(pos_, box_cp_);
}

//-----------------------------------------------------------------------------
//�ړ����x���擾
const float& Character::GetVelocity() const
{
    return velocity_;
}

//-----------------------------------------------------------------------------
//�d�͗L���t���O���擾
bool Character::IsGravity() const
{
    return is_gravity_;
}

//-----------------------------------------------------------------------------
//�n�ʂƐڐG���Ă��邩�擾
bool Character::IsGround() const
{
    auto map = TaskSystem::GetTaskOne<Map::Task>(Map::def_task);
    return map->IsHitFoot(land_rect_.GetOffset(pos_, box_cp_));
}

//-----------------------------------------------------------------------------
//��`��`��
void Character::DrawRect(bool isFill, int color, bool forCam) const
{
    if (forCam)
    {
        land_rect_.GetOffset(GetPosForCam(), box_cp_).DrawRect(isFill, color);
    }
    else
    {
        land_rect_.GetOffset(pos_, box_cp_).DrawRect(isFill, color);
    }
}

//-----------------------------------------------------------------------------
//���Z����ړ��ʂ��擾(�d�͌v�Z���s��)
Math::Vec2 Character::GetVec(const Math::Vec2& direction)
{
    Math::Vec2 vec(direction);

    if (direction != Math::Vec2(0, 0) && is_vel_constant_)
    {
        vec.Normalize();
    }
    vec *= velocity_;

    if (is_gravity_)
    {
        vec += GetAddGravityVec();
    }

    return vec;
}

//-----------------------------------------------------------------------------
//���Z����d�͗ʂ��擾
Math::Vec2 Character::GetAddGravityVec()
{
    grav_cnt_.Run();
    return Math::Vec2(0.f, grav_cnt_.GetNow());
}
