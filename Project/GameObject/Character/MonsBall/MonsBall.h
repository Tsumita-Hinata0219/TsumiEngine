#pragma once

#include "GameObject.h"

class MonsBall {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

private:

	// ノーマルマップ用テクスチャ	
	uint32_t normalMapTexHD_;

	// モデル
	std::unique_ptr<Model> monsBall_[4];

	// ワールドトランスフォーム
	WorldTransform wt_[4];

	// ライト
	DirectionalLight light_{};

};

