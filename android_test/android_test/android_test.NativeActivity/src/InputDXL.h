#pragma once
#include <vector>
#include "DxLib.h"
#include "Math.h"

enum InputState
{
    OFF,    // ������Ă��Ȃ�
    ON,     // ������Ă���
    DOWN,   // �������u��
    UP,     // �������u��
};

enum struct MOUSE_INPUT
{
    LEFT    = 0,    // ���N���b�N
    RIGHT   = 1,    // �E�N���b�N
    MIDDLE  = 2,    // �z�C�[���{�^��
};

enum struct KEY_INPUT
{
    BACK        = 0x0E,     // BackSpace�L�[
    TAB         = 0x0F,     // Tab�L�[
    RETURN      = 0x1C,     // Enter�L�[

    LSHIFT      = 0x2A,     // ��Shift�L�[
    RSHIFT      = 0x36,     // �EShift�L�[
    LCONTROL    = 0x1D,     // ��Ctrl�L�[
    RCONTROL    = 0x9D,     // �ECtrl�L�[
    ESCAPE      = 0x01,     // Esc�L�[
    SPACE       = 0x39,     // �X�y�[�X�L�[
    PGUP        = 0xC9,     // PageUp�L�[
    PGDN        = 0xD1,     // PageDown�L�[
    END         = 0xCF,     // End�L�[
    HOME        = 0xC7,     // Home�L�[
    LEFT        = 0xCB,     // ���L�[
    UP          = 0xC8,     // ��L�[
    RIGHT       = 0xCD,     // �E�L�[
    DOWN        = 0xD0,     // ���L�[	
    INSERT      = 0xD2,     // Insert�L�[
    DEL         = 0xD3,     // Delete�L�[

    MINUS       = 0x0C,     // �|�L�[
    YEN         = 0x7D,     // ���L�[
    PREVTRACK   = 0x90,     // �O�L�[
    PERIOD      = 0x34,     // �D�L�[
    SLASH       = 0x35,     // �^�L�[
    LALT        = 0x38,     // ��Alt�L�[
    RALT        = 0xB8,     // �EAlt�L�[
    SCROLL      = 0x46,     // ScrollLock�L�[
    SEMICOLON   = 0x27,     // �G�L�[
    COLON       = 0x92,     // �F�L�[
    LBRACKET    = 0x1A,     // �m�L�[
    RBRACKET    = 0x1B,     // �n�L�[
    AT          = 0x91,     // ���L�[
    BACKSLASH   = 0x2B,     // �_�L�[
    COMMA       = 0x33,     // �C�L�[
    KANJI       = 0x94,     // �����L�[
    CONVERT     = 0x79,     // �ϊ��L�[
    NOCONVERT   = 0x7B,     // ���ϊ��L�[
    KANA        = 0x70,     // �J�i�L�[
    APPS        = 0xDD,     // �A�v���P�[�V�������j���[�L�[
    CAPSLOCK    = 0x3A,     // CaspLock�L�[
    SYSRQ       = 0xB7,     // PrintScreen�L�[
    PAUSE       = 0xC5,     // PauseBreak�L�[
    LWIN        = 0xDB,     // ��Win�L�[
    RWIN        = 0xDC,     // �EWin�L�[

    NUMLOCK     = 0x45,     // �e���L�[NumLock�L�[
    NUMPAD0     = 0x52,     // �e���L�[0
    NUMPAD1     = 0x4F,     // �e���L�[1
    NUMPAD2     = 0x50,     // �e���L�[2
    NUMPAD3     = 0x51,     // �e���L�[3
    NUMPAD4     = 0x4B,     // �e���L�[4
    NUMPAD5     = 0x4C,     // �e���L�[5
    NUMPAD6     = 0x4D,     // �e���L�[6
    NUMPAD7     = 0x47,     // �e���L�[7
    NUMPAD8     = 0x48,     // �e���L�[8
    NUMPAD9     = 0x49,     // �e���L�[9
    MULTIPLY    = 0x37,     // �e���L�[���L�[
    ADD         = 0x4E,     // �e���L�[�{�L�[
    SUBTRACT    = 0x4A,     // �e���L�[�|�L�[
    DECIMAL     = 0x53,     // �e���L�[�D�L�[
    DIVIDE      = 0xB5,     // �e���L�[�^�L�[
    NUMPADENTER = 0x9C,     // �e���L�[�̃G���^�[�L�[

    F1          = 0x3B,     // F1�L�[
    F2          = 0x3C,     // F2�L�[
    F3          = 0x3D,     // F3�L�[
    F4          = 0x3E,     // F4�L�[
    F5          = 0x3F,     // F5�L�[
    F6          = 0x40,     // F6�L�[
    F7          = 0x41,     // F7�L�[
    F8          = 0x42,     // F8�L�[
    F9          = 0x43,     // F9�L�[
    F10         = 0x44,     // F10�L�[
    F11         = 0x57,     // F11�L�[
    F12         = 0x58,     // F12�L�[

    A           = 0x1E,     // A�L�[
    B           = 0x30,     // B�L�[
    C           = 0x2E,     // C�L�[
    D           = 0x20,     // D�L�[
    E           = 0x12,     // E�L�[
    F           = 0x21,     // F�L�[
    G           = 0x22,     // G�L�[
    H           = 0x23,     // H�L�[
    I           = 0x17,     // I�L�[
    J           = 0x24,     // J�L�[
    K           = 0x25,     // K�L�[
    L           = 0x26,     // L�L�[
    M           = 0x32,     // M�L�[
    N           = 0x31,     // N�L�[
    O           = 0x18,     // O�L�[
    P           = 0x19,     // P�L�[
    Q           = 0x10,     // Q�L�[
    R           = 0x13,     // R�L�[
    S           = 0x1F,     // S�L�[
    T           = 0x14,     // T�L�[
    U           = 0x16,     // U�L�[
    V           = 0x2F,     // V�L�[
    W           = 0x11,     // W�L�[
    X           = 0x2D,     // X�L�[
    Y           = 0x15,     // Y�L�[
    Z           = 0x2C,     // Z�L�[

    NUM0        = 0x0B,     // 0�L�[
    NUM1        = 0x02,     // 1�L�[
    NUM2        = 0x03,     // 2�L�[
    NUM3        = 0x04,     // 3�L�[
    NUM4        = 0x05,     // 4�L�[
    NUM5        = 0x06,     // 5�L�[
    NUM6        = 0x07,     // 6�L�[
    NUM7        = 0x08,     // 7�L�[
    NUM8        = 0x09,     // 8�L�[
    NUM9        = 0x0A,     // 9�L�[
};

enum struct PAD_INPUT
{
    DOWN    = 0,    // �\���{�^����
    LEFT    = 1,    // �\���{�^����
    RIGHT   = 2,    // �\���{�^���E
    UP      = 3,    // �\���{�^����
    A       = 4,    // A�{�^��
    B       = 5,    // B�{�^��
    X       = 6,    // X�{�^��
    Y       = 7,    // Y�{�^��
    L1      = 8,    // L1�{�^��
    R1      = 9,    // R1�{�^��
    SELECT  = 10,   // SELECT�{�^��(BACK�{�^��)
    START   = 11,   // START�{�^��
    L3      = 12,   // L3�{�^��(���X�e�B�b�N��������)
    R3      = 13,   // R3�{�^��(�E�X�e�B�b�N��������)
};

struct ButtonNum
{
    static const int mouse  = 3;
    static const int key    = 256;
    static const int pad    = 28;
};

class InputDXL
{
private:
    //-----------------------------------------------------------------------------
    // ���͏��̊Ǘ�
    class ButtonInfo
    {
    private:
        int duration_time_;
        unsigned int state_;

    public:
        ButtonInfo();
        void SetState(const unsigned int state);
        void AutoSetState(const bool is_button_on);

        const unsigned int& GetInputState() const;
        int GetDurationTime(const unsigned int input_state) const;
        bool operator ==(const unsigned int input_state) const;
        bool operator !=(const unsigned int input_state) const;
    };

    //-----------------------------------------------------------------------------
    // �}�E�X�̓��͏���ێ�����
    class MouseInput
    {
    private:
        ButtonInfo mouse_info_[ButtonNum::mouse];
        Math::Vec2 pos_;
        bool is_input_;

    public:
        MouseInput();

        bool SetInputState();

        const Math::Vec2& GetPos() const;   // �}�E�X�|�C���^�̍��W���擾
        bool IsInput() const;               // ���炩�̓��͂����������ۂ�

        const ButtonInfo& operator [](const MOUSE_INPUT mouse_input) const;
    };

    //-----------------------------------------------------------------------------
    // �L�[�{�[�h�̓��͏���ێ�����
    class KeyInput
    {
    private:
        ButtonInfo key_info_[ButtonNum::key];

    public:
        KeyInput() = default;

        bool SetInputState();

        bool IsInput() const;	// ���炩�̓��͂����������ۂ�

        const ButtonInfo& operator [](const KEY_INPUT key_input_) const;
    };

    //-----------------------------------------------------------------------------
    // �Q�[���p�b�h�̓��͏���ێ�����
    class PadInput
    {
    private:
        unsigned int input_id_;
        ButtonInfo pad_info_[ButtonNum::pad];
        float analog_LX_, analog_LY_,
              analog_RX_, analog_RY_;
        bool is_input_;

    public:
        PadInput(unsigned int id);

        bool SetInputState();

        float GetAngleStickL() const;       // ���X�e�B�b�N�̊p�x���擾
        float GetAngleStickR() const;       // �E�X�e�B�b�N�̊p�x���擾
        float GetVolumeStickL() const;      // ���X�e�B�b�N�̌X���ʂ̑傫�����擾
        float GetVolumeStickR() const;      // �E�X�e�B�b�N�̌X���ʂ̑傫�����擾
        Math::Vec2 GetVecStickL() const;    // ���X�e�B�b�N�̌X���Ɗp�x���x�N�g���Ŏ擾
        Math::Vec2 GetVecStickR() const;    // �E�X�e�B�b�N�̌X���Ɗp�x���x�N�g���Ŏ擾
        bool IsInput() const;               // ���炩�̓��͂����������ۂ�

        const ButtonInfo& operator [](const PAD_INPUT pad_input) const;
    };

    static MouseInput* mouse_;
    static KeyInput* key_;
    static std::vector<PadInput*> pad_;

public:
    // �}�E�X�̃C���X�^���X���擾
    static const MouseInput& GetMouse();
    // �}�E�X�̃C���X�^���X�𐶐�
    static void CreateMouseInstance();
    // �}�E�X�̃C���X�^���X�����
    static void DeleteMouseInstance();
    // �}�E�X�̃C���X�^���X����������Ă��邩�ۂ����擾
    static bool IsCreatedMouseInstance();
    // �}�E�X�̓��͏����擾
    private: static bool GetMouseInputState();

public:
    // �L�[�{�[�h�̃C���X�^���X���擾
    static const KeyInput& GetKey();
    // �L�[�{�[�h�̃C���X�^���X�𐶐�
    static void CreateKeyInstance();
    // �L�[�{�[�h�̃C���X�^���X�����
    static void DeleteKeyInstance();
    // �L�[�{�[�h�̃C���X�^���X����������Ă��邩�ۂ����擾
    static bool IsCreatedKeyInstance();
    // �L�[�{�[�h�̓��͏����擾
    private: static bool GetKeyInputState();

public:
    // �w��ԍ��̃W���C�p�b�h�̃C���X�^���X���擾
    static const PadInput& GetPad(unsigned int id);
    // �w����W���C�p�b�h�̃C���X�^���X�𐶐�
    static void CreatePadInstance(unsigned int pad_num);
    // �W���C�p�b�h�̃C���X�^���X�����
    static void DeletePadInstance();
    // �w��ԍ��̃W���C�p�b�h�̃C���X�^���X����������Ă��邩�ۂ����擾(�f�t�H���g��0��)
    static bool IsCreatedPadInstance(unsigned int id = 0u);
    // �W���C�p�b�h�̓��͏���S�Ď擾
    private: static bool GetPadAllInputState();

public:
    // �S�Ă̓��͏����擾
    static bool GetAllInputState();

    // ���������S�ẴC���X�^���X�����
    static void DeleteAllInstance();
};