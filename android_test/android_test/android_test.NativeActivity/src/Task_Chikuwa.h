#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "Counter.hpp"
#include "ImageDrawer.h"
#include "Task_Physics.h"

namespace Chikuwa
{
    const std::string   task_name("chikuwa");   // タスク名
    
    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;
    
    public:
    
        Resource();     // コンストラクタ
        ~Resource();    // デストラクタ
        static std::shared_ptr<Resource> Create();  // リソースの生成
    };
    
    //----------------------------------------------
    class Task;
    using TaskPtr = std::shared_ptr<Task>;

    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_;  // 確保したリソース
        ImageDrawer drawer_;
        Physics::TaskPtr physics_;

    public:
        //コンストラクタ
        Task(Physics::TaskPtr physics);

        //デストラクタ
        ~Task();

        //タスクの生成
        static std::shared_ptr<Task> Create(Physics::TaskPtr physics);

        void Initialize() override; // 初期化処理
        void Finalize() override;   // 終了処理
        void Update() override;     // 更新
        void Draw() override;       // 描画
    };
}