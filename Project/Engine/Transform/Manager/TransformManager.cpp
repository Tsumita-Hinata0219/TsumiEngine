#include "TransformManager.h"



/// <summary>
/// TransformComponentを新しく作る
/// </summary>
std::weak_ptr<TransformComponent> TransformManager::Create(const std::string& name)
{
	// 名前で検索をかける
	auto it = transformMap_.find(name);
	// 既に存在していたら早期return
	if (it != transformMap_.end())
	{
		return std::weak_ptr<TransformComponent>();
	} 

	// ないので新しく作る
	std::shared_ptr<TransformComponent> newTransform = std::make_shared<TransformComponent>();
	transformMap_[name] = newTransform;

	// 作ったTransformComponentを返す
	return transformMap_[name];
}


/// <summary>
/// 更新処理
/// </summary>
void TransformManager::Update()
{
	// 全てのTransformComponentを更新
	for (auto& it : transformMap_)
	{
		it.second->Update();
	}
}


/// <summary>
/// 取得
/// </summary>
std::weak_ptr<TransformComponent> TransformManager::GetTransform(const std::string& key)
{
	// 名前で検索をかける
	auto it = transformMap_.find(key);
	// なければ空のweak_ptrを返す
	if (it == transformMap_.end())
	{
		return std::weak_ptr<TransformComponent>();
	}

	return it->second;
}
