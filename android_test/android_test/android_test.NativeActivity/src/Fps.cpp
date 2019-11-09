#include "Fps.h"
#include <math.h>
#include "Utility.h"
#include "DxLib.h"

class Fps::Impl
{
private:
    static constexpr int sample_ = 60;  // 平均を取るサンプル数
    static constexpr int set_fps_ = 60; // 設定したFPS
    int start_time_;    // 測定開始時刻
    int count_;         // カウンタ
    float fps_;         // fps
    int before_time_;   // 1フレーム前の時間
    int frame_time_;    // 1フレームの時間

public:
    Impl() :
        start_time_(0),
        count_(0),
        fps_(0),
        before_time_(0),
        frame_time_(0) {}

    // 更新
    void Update()
    {
        int t = GetNowCount();
        // 1フレーム目なら時刻を記憶
        if (count_ == 0) 
        {
            start_time_ = t;
            before_time_ = t;
        }

        // 1フレームの秒数計算
        frame_time_ = t - before_time_;
        before_time_ = t;

        // 60フレーム目なら平均を計算する
        if (count_ == sample_)
        {
            fps_ = 1000.f / ((t - start_time_) / (float)sample_);
            count_ = 0;
            start_time_ = t;
        }
        ++count_;
    }

    // 待機
    void Wait()
    {
        int tookTime = GetNowCount() - start_time_;         // かかった時間
        int waitTime = count_ * 1000 / set_fps_ - tookTime; // 待つべき時間
        if (waitTime > 0)
        {
            WaitTimer(waitTime); // 待機
        }
    }

    // fps表示
    void Draw()
    {
        DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", fps_);
    }

    // 1フレームの秒数を取得
    float GetFrameTime()
    {
        return frame_time_ / 1000.f;
    }
};

//-----------------------------------------------------------------------------
Fps::Impl* Fps::impl_ = nullptr;
Fps::Impl* Fps::GetImpl()
{
    assert(impl_ && "Fps hasn't been created!!");
    return impl_;
}
//-----------------------------------------------------------------------------

// インスタンス生成
void Fps::Create()
{
    if (!impl_)
    {
        impl_ = new Impl();
    }
}

// インスタンス解放
void Fps::Delete()
{
    Util::SafeDelete(impl_);
}

// 更新
void Fps::Update()
{
    GetImpl()->Update();
}

// 待機
void Fps::Wait()
{
    GetImpl()->Wait();
}

// fps表示
void Fps::Draw()
{
    GetImpl()->Draw();
}

// 1フレームの秒数を取得
float Fps::GetFrameTime()
{
    return GetImpl()->GetFrameTime();
}