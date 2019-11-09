#include "GameSystem.h"
#include "DxLib.h"
#include "Fps.h"
#include "SystemDefine.hpp"
#include "TaskSystem.h"
#include "ImageLoader.h"
#include "ShaderManager.h"
#include "Utility.h"

#include "Task_Bg.h"
#include "Task_Chikuwa.h"

GameSystem::GameSystem(){}

//-----------------------------------------------------------------------------
// 初期化処理
void GameSystem::Initialize()
{
    SetAlwaysRunFlag(TRUE); // ウィンドウがノンアクティブでも実行する
    SetOutApplicationLogValidFlag(FALSE); // Log.txtを作らない

    // 背景色設定
    SetBackgroundColor(0, 0, 0);

    // 初期化と裏画面化
    if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
    {
        return;
    }

    int size_x, size_y;
    GetAndroidDisplayResolution(&size_x, &size_y);
    //SysDef::SizeX = size_x;
    //SysDef::SizeY = size_y;

    // 画面解像度とカラービット数設定
    SetGraphMode(size_x, size_y, 32);

    Fps::Create();
    ImageLoader::Create();
    ShaderManager::Create();

    FirstCreateTask();
}

//-----------------------------------------------------------------------------
// メインループ
void GameSystem::MainLoop()
{
    while (Run())
    {
        Fps::Wait();
        Fps::Update();

        // タスクが存在しなかった場合終了する
        if (TaskSystem::GetAllTaskNum() == 0)
        {
            DOUT << "[System End]" << std::endl;
            break;
        }
        TaskSystem::Update();

        TaskSystem::Draw();
        Fps::Draw();
    }
}

//-----------------------------------------------------------------------------
// 終了処理
void GameSystem::Finalize()
{
    Fps::Delete();
    TaskSystem::Delete();
    ImageLoader::Delete();
    ShaderManager::Delete();
    DxLib_End();
}

//-----------------------------------------------------------------------------
// ループを回す際の判定処理
bool GameSystem::Run()
{
    return  ScreenFlip() == 0                               // 裏画面を表画面に反映
        &&  ProcessMessage() == 0                           // メッセージ処理
        &&  ClearDrawScreen() == 0;                         // 画面をクリア
}

//-----------------------------------------------------------------------------
// 最初に作成するタスク
void GameSystem::FirstCreateTask()
{
    // タスクシステムを生成
    TaskSystem::Create();

    //☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
    // ゲーム開始時に作成するタスクを以下に記述 ※警告でるから(void)付けてね
    (void)Bg::Task::Create();
    (void)Chikuwa::Task::Create(nullptr);
}