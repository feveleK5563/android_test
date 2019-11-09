#include "Task_Bg.h"
#include "ImageLoader.h"
#include "InputDXL.h"

namespace Bg
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    // リソースのコンストラクタ
    Resource::Resource()
    {
        ImageLoader::LoadOneImage("background", "bg.png");
    }
    //----------------------------------------------
    // リソースのデストラクタ
    Resource::~Resource()
    {
        ImageLoader::DeleteImageData("background");
    }
    //----------------------------------------------
    // リソースの生成
    std::shared_ptr<Resource> Resource::Create()
    {
        auto sp = instance_.lock();
        if (!sp)
        {
            sp = std::make_shared<Resource>();
            instance_ = sp;
        }
        return sp;
    }

    //☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
    //★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

    //----------------------------------------------
    // タスクのコンストラクタ
    Task::Task()
        : TaskAbstract(task_name, 0.f)
        , res_(Resource::Create())
    {
    }
    //----------------------------------------------
    // タスクのデストラクタ
    Task::~Task()
    {
    }
    //----------------------------------------------
    // タスクの生成
    std::shared_ptr<Task> Task::Create()
    {
        std::shared_ptr<Task> task =
            std::make_shared<Task>();
        TaskSystem::AddTask(task);
        return task;
    }

    //◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
    //◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

    //----------------------------------------------
    // 初期化処理
    //----------------------------------------------
    void Task::Initialize()
    {
        drawer_.Initialize("background", Math::BoxCP::TOP_LEFT);
    }

    //----------------------------------------------
    // 終了処理
    //----------------------------------------------
    void Task::Finalize()
    {
    }

    //----------------------------------------------
    // 更新
    //----------------------------------------------
    void Task::Update()
    {
    }

    //----------------------------------------------
    // 描画
    //----------------------------------------------
    void Task::Draw()
    {
        drawer_.Draw(Math::Vec2(), 0.f, Color(0.9f, 0.9f, 0.9f, 1.f));
    }
}