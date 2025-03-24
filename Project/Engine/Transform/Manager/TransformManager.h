#pragma once

#include "../Structure/Transform.h"


/* Transformを一元管理するクラス */
class TransformManager {

private: // シングルトン

	// コンストラクタ、デストラクタ
	TransformManager() = default;
	~TransformManager() = default;
	TransformManager(const TransformManager&) = delete;
	const TransformManager& operator=(const TransformManager&) = delete;


private:

	/// <summary>
	/// インスタンス取得
	/// </summary>
	static TransformManager* GetInstance() {
		static TransformManager instance;
		return &instance;
	}

	/// <summary>
	/// Transformを新しく作る
	/// </summary>
	std::weak_ptr<Transform> Create(const std::string& name);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 取得
	/// </summary>
	std::weak_ptr<Transform> GetTransform(const std::string& key);

};