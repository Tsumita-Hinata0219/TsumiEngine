#include "CollisionSystem.h"
#include "../Project/GameObject/IObject/IObject.h"



// コンポーネント追加
void CollisionSystem::AAddComponent(CollisionComponent* component)
{
	components_.push_back(component);
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

