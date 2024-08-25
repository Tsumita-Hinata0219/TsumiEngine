#include "CollisionSystem.h"
#include "../Project/GameObject/IObject/IObject.h"


// コンストラクタ
CollisionSystem::CollisionSystem()
{
    //// インデックス初期化
    //shapeIndex_ = 0;
}


// 初期化処理
void CollisionSystem::Init()
{
    // 八分木ノードクラス
    // ルート空間含め孫空間までで空間の深さは4
    node_ = std::make_unique<OctreeNode>(4);

    //// インデックス初期化
    //shapeIndex_ = 0;
}


// コンポーネント追加
void CollisionSystem::AAddComponent(CollisionComponent* component)
{
	components_.push_back(component);
}
void CollisionSystem::AAddComponentN(CollisionComponent* component)
{
    //// コンポーネントの数を取得
    //int index = components_.size();
    //
    //// コンポーネントを八分木クラスに入れる
    //for (int i = 0; i < index; ++i) {
    //    node_->Insert(components_[i]);
    //}
    component;
}


// コンポーネントのクリア
void CollisionSystem::ClearComponent()
{
    components_.clear();
}

//
//// シェイプの追加
//void CollisionSystem::AddShape(CollisionShape* shape)
//{
//    // インデックス加算
//    shapeIndex_++;
//
//    shapes_.push_back(shape);
//}


//// シェイプのクリア
//void CollisionSystem::ClearShape()
//{
//    shapes_.clear();
//}
//

// コリジョン判定を実行
void CollisionSystem::Update()
{
	this->CheckCollisions();
}


// コリジョン判定を行う
void CollisionSystem::CheckCollisions()
{
    size_t count = components_.size();
    
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            
            CollisionComponent* comp1 = components_[i];
            CollisionComponent* comp2 = components_[j];
            
            if (comp1 && comp2) {
                if (comp1->CheckCollision(*comp2)) {
                    CollisionEvent event(comp1, comp2);
                    ColEventManager::GetInstance()->Dispatch(event);


                    comp1->GetOwner()->onCollision(comp2->GetOwner());
                    comp2->GetOwner()->onCollision(comp1->GetOwner());
                }
            }
        }
    }
}

