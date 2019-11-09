#include <iostream>
#include <math.h>
#include "DxLib.h"
#include "InputDXL.h"
#include "Utility.h"

//-----------------------------------------------------------------------------
// �R���X�g���N�^
InputDXL::ButtonInfo::ButtonInfo() :
    duration_time_(0),
    state_(OFF) {}

//-----------------------------------------------------------------------------
// ��Ԃ̐ݒ�Ə�Ԏ������Ԃ̌v��
void InputDXL::ButtonInfo::SetState(const unsigned int setState)
{
    if (state_ == setState)
    {
        ++duration_time_;
    }
    else
    {
        duration_time_ = 0;
    }
    state_ = setState;
}

//-----------------------------------------------------------------------------
// ���͏󋵂����Ԃ�ݒ�
void InputDXL::ButtonInfo::AutoSetState(const bool isButtonOn)
{
    if (isButtonOn)
    {
        if (state_ == InputState::DOWN || state_ == InputState::ON)
        {
            SetState(InputState::ON);
        }
        else
        {
            SetState(InputState::DOWN);
        }
    }
    else
    {
        if (state_ == InputState::UP || state_ == InputState::OFF)
        {
            SetState(InputState::OFF);
        }
        else
        {
            SetState(InputState::UP);
        }
    }
}

//-----------------------------------------------------------------------------
// ��Ԃ̎擾
const unsigned int& InputDXL::ButtonInfo::GetInputState() const
{
    return state_;
}

//-----------------------------------------------------------------------------
// ��Ԏ������Ԃ��擾
int InputDXL::ButtonInfo::GetDurationTime(const unsigned int instate) const
{
    if (state_ == instate)
    {
        return duration_time_;
    }
    return -1;
}

//-----------------------------------------------------------------------------
// ��Ԃ̔�r(��v)
bool InputDXL::ButtonInfo::operator ==(const unsigned int instate) const
{
    return state_ == instate;
}

//-----------------------------------------------------------------------------
// ��Ԃ̔�r(�s��v)
bool InputDXL::ButtonInfo::operator!=(const unsigned int instate) const
{
    return state_ != instate;
}


//-----------------------------------------------------------------------------
// �R���X�g���N�^
InputDXL::MouseInput::MouseInput():
    pos_(0.f, 0.f),
    is_input_(false){}

//-----------------------------------------------------------------------------
// �}�E�X���͏����󂯎��
bool InputDXL::MouseInput::SetInputState()
{
    int state = GetMouseInput();
    for (int i = 0; i < ButtonNum::mouse; ++i)
    {
        mouse_info_[i].AutoSetState(state & (1 << i));
    }
    is_input_ = state > 0;

    int x, y;
    GetMousePoint(&x, &y);
    pos_.x = (float)x;
    pos_.y = (float)y;

    return true;
}
//-----------------------------------------------------------------------------
// �}�E�X�̍��W���擾����
const Math::Vec2& InputDXL::MouseInput::GetPos() const
{
    return pos_;
}
//-----------------------------------------------------------------------------
// ���炩�̓��͂����������ۂ�
bool InputDXL::MouseInput::IsInput() const
{
    return is_input_;
}
//-----------------------------------------------------------------------------
// �w��{�^���̎����͏����擾����
const InputDXL::ButtonInfo& InputDXL::MouseInput::operator [](const MOUSE_INPUT mouseInput) const
{
    return mouse_info_[(int)mouseInput];
}


//-----------------------------------------------------------------------------
// �L�[���͏����󂯎��
bool InputDXL::KeyInput::SetInputState()
{
    char getHitKeyStateAll_Key[ButtonNum::key];
    GetHitKeyStateAll(getHitKeyStateAll_Key);
    for (int i = 0; i < ButtonNum::key; ++i)
    {
        key_info_[i].AutoSetState(getHitKeyStateAll_Key[i]);
    }
    return true;
}
//-----------------------------------------------------------------------------
// ���炩�̓��͂����������ۂ�
bool InputDXL::KeyInput::IsInput() const
{
    return CheckHitKeyAll() == 0;
}
//-----------------------------------------------------------------------------
// �w��L�[�̎����͏����擾����
const InputDXL::ButtonInfo& InputDXL::KeyInput::operator [](const KEY_INPUT key_input) const
{
    return key_info_[(int)key_input];
}


//-----------------------------------------------------------------------------
// �R���X�g���N�^(�W���C�p�b�h�̔ԍ���ݒ肷��)
InputDXL::PadInput::PadInput(unsigned int id):
    input_id_(id),
    analog_LX_(0.f), analog_LY_(0.f),
    analog_RX_(0.f), analog_RY_(0.f),
    is_input_(false){}

//-----------------------------------------------------------------------------
// �W���C�p�b�h�̓��͏����󂯎��
bool InputDXL::PadInput::SetInputState()
{
    int state = GetJoypadInputState(input_id_);
    for (int i = 0; i < ButtonNum::pad; ++i)
    {
        pad_info_[i].AutoSetState(state & (1 << i));
    }
    is_input_ = state > 0;

    int lx, ly, rx, ry;
    GetJoypadAnalogInput(&lx, &ly, input_id_);
    GetJoypadAnalogInputRight(&rx, &ry, input_id_);
    analog_LX_ = float(lx) / 1000.f;
    analog_LY_ = float(ly) / 1000.f;
    analog_RX_ = float(rx) / 1000.f;
    analog_RY_ = float(ry) / 1000.f;

    return true;
}
//-----------------------------------------------------------------------------
// ���X�e�B�b�N�̊p�x���擾����
float InputDXL::PadInput::GetAngleStickL() const
{
    return atan2f(analog_LY_, analog_LX_);
}
//-----------------------------------------------------------------------------
// �E�X�e�B�b�N�̊p�x���擾����
float InputDXL::PadInput::GetAngleStickR() const
{
    return atan2f(analog_RY_, analog_RX_);
}
//-----------------------------------------------------------------------------
// ���X�e�B�b�N�̌X���ʂ��擾����(0.0f~1.0f)
float InputDXL::PadInput::GetVolumeStickL() const
{
    return min(std::sqrtf(analog_LX_ * analog_LX_ + analog_LY_ * analog_LY_), 1.f);
}
//-----------------------------------------------------------------------------
// �E�X�e�B�b�N�̌X���ʂ��擾����(0.0f~1.0f)
float InputDXL::PadInput::GetVolumeStickR() const
{
    return min(std::sqrtf(analog_RX_ * analog_RX_ + analog_RY_ * analog_RY_), 1.f);
}
//-----------------------------------------------------------------------------
// ���X�e�B�b�N�̌X���Ɗp�x���x�N�g���Ŏ擾
Math::Vec2 InputDXL::PadInput::GetVecStickL() const
{
    Math::Vec2 vec;
    vec.x = cos(GetAngleStickL());
    vec.y = sin(GetAngleStickL());
    vec *= GetVolumeStickL();
    return vec;
}
//-----------------------------------------------------------------------------
// �E�X�e�B�b�N�̌X���Ɗp�x���x�N�g���Ŏ擾
Math::Vec2 InputDXL::PadInput::GetVecStickR() const
{
    Math::Vec2 vec;
    vec.x = cos(GetAngleStickR());
    vec.y = sin(GetAngleStickR());
    vec *= GetVolumeStickR();
    return vec;
}
//-----------------------------------------------------------------------------
// ���炩�̓��͂����������ۂ�
bool InputDXL::PadInput::IsInput() const
{
    return is_input_;
}
//-----------------------------------------------------------------------------
// �w��{�^���̓��͏����擾����
const InputDXL::ButtonInfo& InputDXL::PadInput::operator [](const PAD_INPUT padInput) const
{
    return pad_info_[(int)padInput];
}



InputDXL::MouseInput* InputDXL::mouse_ = nullptr;
//-----------------------------------------------------------------------------
// �}�E�X�̃C���X�^���X���擾
const InputDXL::MouseInput& InputDXL::GetMouse()
{
    assert(IsCreatedMouseInstance() && "MouseInput hasn't been created!");
    return *mouse_;
}
//-----------------------------------------------------------------------------
// �}�E�X�̃C���X�^���X�𐶐�
void InputDXL::CreateMouseInstance()
{
    if (!IsCreatedMouseInstance())
    {
        mouse_ = new MouseInput();
    }
}
//-----------------------------------------------------------------------------
// �}�E�X�̃C���X�^���X���������
void InputDXL::DeleteMouseInstance()
{
    Util::SafeDelete(mouse_);
}
//-----------------------------------------------------------------------------
// �}�E�X�̃C���X�^���X����������Ă��邩�ۂ����擾
bool InputDXL::IsCreatedMouseInstance()
{
    if (mouse_ != nullptr) { return true; }
    return false;
}
//-----------------------------------------------------------------------------
// �}�E�X�̓��͏����擾����
bool InputDXL::GetMouseInputState()
{
    if (!IsCreatedMouseInstance()) { return true; }
    return mouse_->SetInputState();
}

InputDXL::KeyInput* InputDXL::key_ = nullptr;
//-----------------------------------------------------------------------------
// �L�[�{�[�h�̃C���X�^���X���擾
const InputDXL::KeyInput& InputDXL::GetKey()
{
    assert(IsCreatedKeyInstance() && "KeyInput hasn't been created!");
    return *key_;
}
//-----------------------------------------------------------------------------
// �L�[�{�[�h�̃C���X�^���X�𐶐�
void InputDXL::CreateKeyInstance()
{
    if (!IsCreatedKeyInstance())
    {
        key_ = new KeyInput();
    }
}
//-----------------------------------------------------------------------------
// �L�[�{�[�h�̃C���X�^���X���������
void InputDXL::DeleteKeyInstance()
{
    Util::SafeDelete(key_);
}
//-----------------------------------------------------------------------------
// �L�[�{�[�h�̃C���X�^���X����������Ă��邩�ۂ����擾
bool InputDXL::IsCreatedKeyInstance()
{
    if (key_ != nullptr) { return true; }
    return false;
}
//-----------------------------------------------------------------------------
// �L�[�{�[�h�̓��͏����擾����
bool InputDXL::GetKeyInputState()
{
    if (!IsCreatedKeyInstance()) { return true; }
    return key_->SetInputState();
}

std::vector<InputDXL::PadInput*> InputDXL::pad_;
//-----------------------------------------------------------------------------
// �W���C�p�b�h�̃C���X�^���X���擾
const InputDXL::PadInput& InputDXL::GetPad(unsigned int id)
{
    assert(IsCreatedPadInstance(id) && "PadInput hasn't been created!");
    return *pad_[id];
}
//-----------------------------------------------------------------------------
// �W���C�p�b�h�̃C���X�^���X�𐶐�
void InputDXL::CreatePadInstance(unsigned int padNum)
{
    // �������񃊃Z�b�g���Ă���Đ�������
    DeletePadInstance();
    pad_.resize(padNum);
    for (unsigned int i = 0; i < padNum; ++i)
    {
        pad_[i] = new PadInput(i + 1);
    }
}
//-----------------------------------------------------------------------------
// �W���C�p�b�h�̃C���X�^���X���������
void InputDXL::DeletePadInstance()
{
    if (pad_.size() <= 0) { return; }

    for (auto& it : pad_)
    {
        Util::SafeDelete(it);
    }
    pad_.clear();
    pad_.shrink_to_fit();
}
//-----------------------------------------------------------------------------
// �w��ԍ��̃W���C�p�b�h�̃C���X�^���X����������Ă��邩�ۂ����擾
bool InputDXL::IsCreatedPadInstance(unsigned int id)
{
    if (id >= pad_.size()) { return false; }
    return true;
}
//-----------------------------------------------------------------------------
// �W���C�p�b�h�̓��͏���S�Ď擾����
bool InputDXL::GetPadAllInputState()
{
    bool isCompleteInput = true;
    for (auto& it : pad_)
    {
        isCompleteInput = isCompleteInput && it->SetInputState();
    }
    return isCompleteInput;
}

//-----------------------------------------------------------------------------
// ���͏����擾
bool InputDXL::GetAllInputState()
{
    return GetMouseInputState() &&
           GetKeyInputState() &&
           GetPadAllInputState();
}

//-----------------------------------------------------------------------------
// ���������S�ẴC���X�^���X�����
void InputDXL::DeleteAllInstance()
{
    DeleteMouseInstance();
    DeleteKeyInstance();
    DeletePadInstance();
}