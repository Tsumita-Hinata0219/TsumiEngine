#include "CollisionSystem.h"
#include "GameObject/IObject/IObject.h"


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
    //node_ = std::make_unique<OctreeNode>(4);

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
    component;
}


// コンポーネントのクリア
void CollisionSystem::ClearComponent()
{
    components_.clear();
}


// コリジョン判定を実行
void CollisionSystem::Update()
{
	this->CheckCollisions();
}


// シェイプの追加
void CollisionSystem::RegisterShape(ColShapeData& data)
{
    // Indexの加算
    shapeIndex_++;
    data;
    
    //if (auto colData = std::get_if<Col::Sphere>(&data)) {

    //    // IDの設定
    //    colData->id = shapeIndex_;

    //}
    //else if (auto colData = std::get_if<Col::AABB>(&data)) {

    //    // IDの設定
    //    colData->id = shapeIndex_;
    //}
    //else if (auto colData = std::get_if<Col::OBB>(&data)) {

    //    // IDの設定
    //    colData->id = shapeIndex_;
    //}
    //else if (auto colData = std::get_if<Col::Segment>(&data)) {

    //    // IDの設定
    //    colData->id = shapeIndex_;
    //}
    //else if (auto colData = std::get_if<Col::Capsule>(&data)) {

    //    // IDの設定
    //    colData->id = shapeIndex_;
    //}
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

