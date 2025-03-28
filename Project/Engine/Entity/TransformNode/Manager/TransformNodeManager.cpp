#include "TransformNodeManager.h"



/// <summary>
/// TransformNodeを新しく作る
/// </summary>
std::weak_ptr<TransformNode> TransformNodeManager::Create(const std::string& name)
{
	// 名前で検索をかける
	auto it = transformMap_.find(name);
	// 既に存在していたら早期return
	if (it != transformMap_.end())
	{
		return std::weak_ptr<TransformNode>();
	}

	// ないので新しく作る
	std::shared_ptr<TransformNode> newTransform = std::make_shared<TransformNode>();
	transformMap_[name] = newTransform;

	// 作ったTransformNodeを返す
	return transformMap_[name];
}


/// <summary>
/// 更新処理
/// </summary>
void TransformNodeManager::Update()
{
	// 全てのTransformNodeを更新
	for (auto& it : transformMap_)
	{
		it.second->Update();
	}
}


/// <summary>
/// 取得
/// </summary>
std::weak_ptr<TransformNode> TransformNodeManager::GetTransform(const std::string& key)
{
	// 名前で検索をかける
	auto it = transformMap_.find(key);
	// なければ空のweak_ptrを返す
	if (it == transformMap_.end())
	{
		return std::weak_ptr<TransformNode>();
	}

	return it->second;
}


/// <summary>
/// CBVのバインド
/// </summary>
void TransformNodeManager::Bind_CBV(const std::string& key, UINT num)
{
	// 名前で検索をかける
	auto it = transformMap_.find(key);
	// なければ空のweak_ptrを返す
	if (it == transformMap_.end())
	{
		return;
	}

	it->second->Bind_CBV(num);
}
