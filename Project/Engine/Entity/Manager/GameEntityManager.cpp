#include "GameEntityManager.h"



/// <summary>
/// Entityの追加処理
/// </summary>
void GameEntityManager::Add_NewEntity(std::shared_ptr<IActor> actor)
{
	std::string name = actor->GetName();

	// 名前で検索をかける
	auto it = eneityMap_.find(name);
	// 既に存在していたら早期return	
	if (it != eneityMap_.end())
	{
		return;
	}

	// ないので新しく作る
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>();

	// 名前の設定
	newEntity->name = name;

	// Actorの設定と初期化
	newEntity->actor = actor;
	newEntity->actor->Init();

	// TransformNodeの生成
	newEntity->transformNode = std::make_shared<TransformNode>(name);


	// Mapに追加
	this->eneityMap_[name] = newEntity;
}


/// <summary>
/// 更新処理
/// </summary>
void GameEntityManager::Update_Entity()
{
	float deltaTime = 1.0f / 60.0f;

	for(auto& entity : this->eneityMap_)
	{
		// Actorの更新
		entity.second->actor->Update(deltaTime);
		// TransformNodeの更新
		entity.second->transformNode->Update();
	}
}


/// <summary>
/// 描画処理
/// </summary>
void GameEntityManager::Render_Entity()
{
	for (auto& entity : this->eneityMap_)
	{
		// Actorの描画
		entity.second->actor->Render();
	}
}


/// <summary>
/// クリア
/// </summary>
void GameEntityManager::Clear_Entity()
{
	this->eneityMap_.clear();
}


/// <summary>
/// 特定のActorを取得する
/// </summary>
std::weak_ptr<IActor> GameEntityManager::Get_Actor(const std::string& key)
{
	auto it = this->eneityMap_.find(key);
	if (it != this->eneityMap_.end())
	{
		return it->second->actor;
	}
	return std::weak_ptr<IActor>(); // 見つからなければ空を返す
}


/// <summary>
/// 特定のActorの状態を取得する
/// </summary>
IActor::State GameEntityManager::Get_ActorState(const std::string& key)
{
	auto it = this->eneityMap_.find(key);
	if (it != this->eneityMap_.end())
	{
		return it->second->actor->GetState();
	}
	return IActor::State::None; // 見つからなければNoneを返す
}


/// <summary>
/// 特定のActorの状態を設定する
/// </summary>
void GameEntityManager::Set_ActorState(const std::string& key, IActor::State state)
{
	auto it = this->eneityMap_.find(key);
	if (it != this->eneityMap_.end())
	{
		it->second->actor->SetState(state);
	}
	return; // 見つからなければ何もしない
}


/// <summary>
/// 全てのActorの状態を設定する
/// </summary>
void GameEntityManager::Set_AllActorState(IActor::State state)
{
	for (auto& entity : this->eneityMap_)
	{
		entity.second->actor->SetState(state);
	}
}


/// <summary>
/// 特定のTransformNodeを取得する
/// </summary>
std::weak_ptr<TransformNode> GameEntityManager::Get_TransformNode(const std::string& key)
{
	auto it = this->eneityMap_.find(key);
	if (it != this->eneityMap_.end())
	{
		return it->second->transformNode;
	}
	return std::weak_ptr<TransformNode>(); // 見つからなければ空を返す
}
