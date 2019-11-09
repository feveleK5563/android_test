#include "Utility.h"
#include <windows.h>

namespace Util
{
    Console::Console()
    {
        AllocConsole();
        freopen_s(&in_, "CONIN$", "r", stdin);      // �W�����͂��R���\�[���ɂ���
        freopen_s(&out_, "CONOUT$", "w", stdout);   // �W���o�͂��R���\�[���ɂ���
    }
    Console::~Console()
    {
        std::fclose(in_);
        std::fclose(out_);
        FreeConsole();
    }
}