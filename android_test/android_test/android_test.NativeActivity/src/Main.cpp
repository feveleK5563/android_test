#include "DxLib.h"
#include "GameSystem.h"
#include "Utility.h"

// プログラムは android_main から始まります
int android_main(void)
{
    GameSystem gs;
    gs.Initialize();

    gs.MainLoop();

    gs.Finalize();
    return 0;
}