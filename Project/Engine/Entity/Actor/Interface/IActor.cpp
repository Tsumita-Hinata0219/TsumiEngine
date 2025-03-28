#include "IActor.h"
#include "../../Component/Interface/IComponent.h"
#include "Entity/TransformNode/Manager/TransformNodeManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
IActor::IActor()
{
	// ステートはActiveに
	state_ = State::Active;
}


/// <summary>
/// デストラクタ
/// </summary>
IActor::~IActor()
{
	// ComponentListのClear
	components_.clear();
}


/// <summary>
/// 生成
/// </summary>
void IActor::Create(std::string name)
{
	// 名前の設定
	name_ = name;

	// TransformNodeの作成
	auto manager = TransformNodeManager::GetInstance();
	transNode_ = manager->Create(name_);
}


/// <summary>
/// 更新処理関係
/// </summary>
void IActor::Update(float deltaTime)
{
	// ステートアクティブ時、更新
	if (state_ == State::Active) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}
void IActor::UpdateComponents([[maybe_unused]] float deltaTime) 
{
	for (auto& component : components_) {
		component->Update(deltaTime);
	}

}
void IActor::UpdateActor([[maybe_unused]] float deltaTime) {}


/// <summary>
/// 描画処理
/// </summary>
void IActor::Render()
{

}


/// <summary>
/// コンポーネントの追加
/// </summary>
void IActor::AddComponent(std::shared_ptr<IComponent> component)
{
	components_.push_back(component);
}


/// <summary>
/// Renderコンポーネントの追加
/// </summary>
void IActor::AddRenderComponent(std::shared_ptr<IComponent> component)
{
	renderComponent_.push_back(component);
}


/// <summary>
/// コンポーネント削除
/// </summary>
void IActor::RemoveComponent(std::shared_ptr<IComponent> component)
{
	auto itr = std::find(components_.begin(), components_.end(), component);
	if (itr != components_.end()) {
		components_.erase(itr);
	}
}

