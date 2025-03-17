#include "IActor.h"
#include "../../Component/Interface/IComponent.h"


/// <summary>
/// コンストラクタ
/// </summary>
IActor::IActor()
{
	// ステートはActiveに
	state = State::Active;

	// Transformの初期化
	transform.Init();
}


/// <summary>
/// デストラクタ
/// </summary>
IActor::~IActor()
{
	// ComponentListのClear
	componentList.clear();
}


/// <summary>
/// 更新処理関係
/// </summary>
void IActor::Update(float deltaTime)
{
	// ステートアクティブ時、更新
	if (state == State::Active) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}
void IActor::UpdateComponents([[maybe_unused]] float deltaTime) 
{
	for (auto& component : componentList) {
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
	int myOrder = component->GetUpdateOrder();
	auto itr = componentList.begin();
	for (; itr != componentList.end(); itr++) {
		if (myOrder < (*itr)->GetUpdateOrder()) {
			break;
		}
	}
	componentList.insert(itr, component);
}


/// <summary>
/// コンポーネント削除
/// </summary>
void IActor::RemoveComponent(std::shared_ptr<IComponent> component)
{
	auto itr = std::find(componentList.begin(), componentList.end(), component);
	if (itr != componentList.end()) {
		componentList.erase(itr);
	}
}

