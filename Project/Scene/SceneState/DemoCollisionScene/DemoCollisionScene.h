#pragma once

#include "IScene.h"
#include "GameManager.h"
#include "ViewProjection.h"
#include "GameObject.h"

class DemoCollisionScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	DemoCollisionScene() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DemoCollisionScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(GameManager* state) override;

	/// <summary>
	/// 背景スプライトの描画処理
	/// </summary>
	void BackSpriteDraw() override;

	/// <summary>
	/// ３Dオブジェクトの描画処理
	/// </summary>
	void ModelDraw() override;

	/// <summary>
	/// 前景スプライトの描画処理
	/// </summary>
	void FrontSpriteDraw() override;


private:

	ViewProjection viewProjection_{};


	// カプセルモデル
	std::unique_ptr<Model> capsuleObj_;

	// カプセルワールドトランスフォーム
	WorldTransform capsuleWt_{};

	// カプセルライト
	DirectionalLight capsuleLight_{};

	// カプセルカラー
	Vector4 capsuleColor_ = Vector4::one;
};

