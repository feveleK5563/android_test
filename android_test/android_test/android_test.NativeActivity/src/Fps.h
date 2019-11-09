#pragma once

class Fps
{
public:
    // インスタンス生成
    static void Create();
    // インスタンス解放
    static void Delete();

    // 更新
    static void Update();
    // 待機
    static void Wait();
    // fps表示
    static void Draw();
    // 1フレームの秒数を取得
    static float GetFrameTime();

private:
    class Impl;
    static Impl* impl_;
    static Impl* GetImpl();
};