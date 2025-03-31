#include "IActor.h"
#include "../../Component/Interface/IComponent.h"
#include "../../Component/Render/IRenderComponent.h"
#include "Entity/TransformNode/Manager/TransformNodeManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
IActor::IActor()
{
	// ステートはActiveに
	state_ = State::Active;

	// 名前はdefaultで初期化
	name_ = "default";
}


/// <summary>
/// デストラクタ
/// </summary>
IActor::~IActor()
{
	// ComponentMapのClear
	componentMap_.clear();
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
	for (auto& component : componentMap_) {
		component.second->Update(deltaTime);
	}
	if (isRender_) {
		renderComponent_->Update();
	}
}


/// <summary>
/// 描画処理
/// </summary>
void IActor::Render()
{
	if (isRender_) {
		renderComponent_->Draw();
	}
}


/// <summary>
/// コンポーネントの追加
/// </summary>
void IActor::AddComponent(std::shared_ptr<IComponent> component)
{
	// 名前で検索をかける
	auto it = componentMap_.find(component->Get_Name());
	// 既に存在していたら早期return
	if (it != componentMap_.end())
	{
		return;
	}

	// なければMapに追加
	componentMap_[component->Get_Name()] = component;
}


/// <summary>
/// Renderコンポーネントの追加
/// </summary>
void IActor::AddRenderComponent(std::shared_ptr<IRenderComponent> component)
{
	renderComponent_ = component;
	isRender_ = true;
}


/// <summary>
/// ComponentのWeakPtr取得
/// </summary>
std::weak_ptr<IComponent> IActor::GetComponent(const std::string& name)
{
	// 名前で検索をかける
	auto it = componentMap_.find(name);
	// なければ空のweak_ptrを返す
	if (it == componentMap_.end())
	{
		return std::weak_ptr<IComponent>();
	}

	return it->second;
}


/// <summary>
/// RenderComponentのWeakPtr取得
/// </summary>
std::weak_ptr<IRenderComponent> IActor::GetRenderComponent()
{
	// componentがnullなら空のweak_ptrを返す
	if (!renderComponent_) {
		return std::weak_ptr<IRenderComponent>();
	}

	return renderComponent_;
}
