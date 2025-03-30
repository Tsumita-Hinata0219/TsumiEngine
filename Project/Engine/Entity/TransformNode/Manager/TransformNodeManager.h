#pragma once


#include "../Node/TransformNode.h"


/* TransformNodeを一元管理するクラス */
class TransformNodeManager {

private:

	std::unordered_map<std::string, std::shared_ptr<TransformNode>> transformMap_;

private: // シングルトン

	// コンストラクタ、デストラクタ
	TransformNodeManager() = default;
	~TransformNodeManager() = default;
	TransformNodeManager(const TransformNodeManager&) = delete;
	const TransformNodeManager& operator=(const TransformNodeManager&) = delete;


public:

	/// <summary>
	/// インスタンス取得
	/// </summary>
	static TransformNodeManager* GetInstance() {
		static TransformNodeManager instance;
		return &instance;
	}

	/// <summary>
	/// Transformを新しく作る
	/// </summary>
	std::weak_ptr<TransformNode> Create(const std::string& name);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 取得
	/// </summary>
	std::weak_ptr<TransformNode> GetTransform(const std::string& key);

	/// <summary>
	/// CBVのバインド
	/// </summary>
	void Bind_CBV(const std::string& key, UINT num);

	/// <summary>
	/// transformMap_のクリア
	/// </summary>
	void Clear();
};