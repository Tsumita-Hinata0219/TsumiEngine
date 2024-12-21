#include "IActor.h"
#include "../../Component/Interface/IComponent.h"


/// <summary>
/// コンストラクタ
/// </summary>
IActor::IActor()
{
	// Transformの初期化
	transform.Init();

	// ステートはActiveに
	state = State::Active;
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
void IActor::UpdateComponents([[maybe_unused]] float deltaTime) {}
void IActor::UpdateActor([[maybe_unused]] float deltaTime) {}


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

