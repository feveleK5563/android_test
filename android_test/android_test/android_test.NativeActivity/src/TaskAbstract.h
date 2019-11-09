#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Utility.h"

enum struct TaskState
{
    Active,     // 0.通常
    Sleep,      // 1.更新停止
    DeepSleep,  // 2.更新と描画停止
    Kill,       // 3.消滅要請
    Delete,     // 4.強制消滅(普通は使わない)
}; 

class TaskAbstract
{
private:
    const std::string   task_name_;     // タスク名
    float               priority_;      // 描画優先度
    TaskState           task_state_;    // 状態
    const TaskState*    parent_state_;  // 親の状態

public:
    // コンストラクタ
    TaskAbstract(const std::string& task_name, float priority);

    // デストラクタ
    virtual ~TaskAbstract();

    virtual void Initialize() = 0;  // 初期化処理(必須)
    virtual void Finalize() = 0;    // 終了処理(必須)
    virtual void Update() {};       // 更新
    virtual void Draw() {};         // 描画

    virtual void SetTaskState(TaskState task_state);    // タスクの状態を設定
    void SetPriority(float set_priority);               // 描画優先度を設定
    void Kill();                                        // 消滅要請状態に設定

    const std::string&  GetTaskName() const;  // タスク名を取得
    const float&        GetPriority() const;  // 描画優先度を取得
    const TaskState&    GetTaskState() const; // タスクの状態を取得

    // 他タスクとの親子関係設定
    void SetParentTask(const TaskAbstract* const parent_task);
    // 親子関係解除
    void ReleaceParentTask();
};