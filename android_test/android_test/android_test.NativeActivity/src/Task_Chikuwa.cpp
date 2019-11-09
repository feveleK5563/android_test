#include "Task_Chikuwa.h"
#include "ImageLoader.h"
#include "SystemDefine.hpp"
#include "Fps.h"

namespace Chikuwa
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    // リソースのコンストラクタ
    Resource::Resource()
    {
        ImageLoader::LoadOneImage("chikuwa", "chikuwa.png");
    }
    //----------------------------------------------
    // リソースのデストラクタ
    Resource::~Resource()
    {
        ImageLoader::DeleteImageData("chikuwa");
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
    Task::Task(Physics::TaskPtr physics)
        : TaskAbstract(task_name, 1.f)
        , res_(Resource::Create())
    {
        if (physics)
        {
            physics_ = physics;
        }
    }
    //----------------------------------------------
    // タスクのデストラクタ
    Task::~Task()
    {
    }
    //----------------------------------------------
    // タスクの生成
    std::shared_ptr<Task> Task::Create(Physics::TaskPtr physics)
    {
        std::shared_ptr<Task> task =
            std::make_shared<Task>(physics);
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
        if (!physics_)
        {
            physics_ = Physics::Task::Create();
            physics_->SetPos(Math::Vec2(SysDef::SizeX / 2, SysDef::SizeY / 2));
        }
        physics_->SetParentTask(this);

        drawer_.Initialize("chikuwa", Math::BoxCP::CENTER);
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
        drawer_.SetScale(3.f);
        drawer_.Draw(physics_->GetPos(),
                    physics_->GetAngRad());
    }
}