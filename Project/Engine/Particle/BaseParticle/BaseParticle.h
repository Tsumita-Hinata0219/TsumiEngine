#pragma once

#include "GameObject/GameObject.h"


/* ベースパーティクルクラス */
class BaseParticle {

public:

	/// <summary>
	/// コンストラクト
	/// </summary>
	BaseParticle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BaseParticle() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw3D();


private:

	// CameraManager
	CameraManager* cameraManager_ = nullptr;
	
	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};

};

