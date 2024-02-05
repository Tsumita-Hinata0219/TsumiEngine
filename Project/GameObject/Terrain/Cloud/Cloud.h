#pragma once

#include "GameObject.h"

class Cloud {

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

	// テクスチャハンドル	
	uint32_t cloudTexHD_;

	// スプライト
	std::unique_ptr<Sprite> sprite_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform wt_{};



};

