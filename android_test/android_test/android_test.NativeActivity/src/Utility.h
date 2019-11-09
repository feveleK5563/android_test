#pragma once
#include <cstdio>
#include <iostream>

// �ȉ��̃}�N���̍쐬�҂͐A�R�Ȃ̂Ŗ�肪��������A�R�̂���
#ifdef _DEBUG
// �f�o�b�O���ɃR���\�[����\������
#define ShowConsole() Util::Console c
// �f�o�b�O���ɃR���\�[����ʂ֏o��
#define DOUT std::cout
// �t�@�C�����ƍs�����R���\�[����ʂ֏o��
#define FILE_AND_LINE std::cout << __FILE__ << ":" << __LINE__ << std::endl

#else
// �f�o�b�O�p�̂��ꂱ��𖳎�����
#define NDEBUG	// assert����
#define ShowConsole() __noop
#define DOUT false && std::cout
#define FILE_AND_LINE false

#endif
#include <assert.h>


namespace Util
{
    // ���|�C���^�����S��delete����
    template<class T>void SafeDelete(T& t)
    {
        if (t != nullptr)
        {
            delete t;
            t = nullptr;
        }
    }

    // ���|�C���^�����S��delete����(�z���)
    template<class T>void SafeDeleteArr(T& t)
    {
        if (t != nullptr)
        {
            delete[] t;
            t = nullptr;
        }
    }

    // �R���\�[����ʂ��o���Acout,cin��������
    class Console final
    {
    private:
        std::FILE* in_;
        std::FILE* out_;

    public:
        Console();
        ~Console();
    };
}