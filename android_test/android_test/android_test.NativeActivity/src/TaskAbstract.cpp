#include "TaskAbstract.h"

TaskAbstract::TaskAbstract(const std::string& task_name,
                           float priority):
    task_name_(task_name),
    priority_(priority),
    task_state_(TaskState::Active),
    parent_state_(nullptr)
{
    DOUT << "【Create Task】Task:" << task_name_ << std::endl;
}

TaskAbstract::~TaskAbstract()
{
    DOUT << "【Delete Task】Task:" << task_name_ << std::endl;
}

// 描画優先度を設定
void TaskAbstract::SetPriority(float set_priority)
{
    priority_ = set_priority;
}

// タスクの状態を設定
void TaskAbstract::SetTaskState(TaskState task_state)
{
    task_state_ = task_state;
}

// 消滅要請状態に設定
void TaskAbstract::Kill()
{
    task_state_ = TaskState::Kill;
}

// タスク名を取得
const std::string& TaskAbstract::GetTaskName() const
{
    return task_name_;
}

// 描画優先度を取得
const float& TaskAbstract::GetPriority() const
{
    return priority_;
}

// タスクの状態を取得
const TaskState& TaskAbstract::GetTaskState() const
{
    if ((!parent_state_) ||
        (task_state_ > *parent_state_))
    {
        return task_state_;
    }
    else
    {
        return *parent_state_;
    }
}

// 他タスクとの親子関係設定
void TaskAbstract::SetParentTask(const TaskAbstract* const parent_task)
{
    parent_state_ = &(parent_task->GetTaskState());
}

// 親子関係解除
void TaskAbstract::ReleaceParentTask()
{
    parent_state_ = nullptr;
}