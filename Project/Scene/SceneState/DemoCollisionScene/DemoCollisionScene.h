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


	// カプセル1
	std::unique_ptr<Model> capsuleObj1_;
	WorldTransform capsuleWt1_{};
	Vector4 capsuleColor1_ = Vector4::one;

	// カプセル2
	std::unique_ptr<Model> capsuleObj2_;
	WorldTransform capsuleWt2_{};
	Vector4 capsuleColor2_ = { 0.0f, 0.0f, 1.0f, 1.0f };

	// カプセルライト
	DirectionalLight capsuleLight_{};

	int timer = 0;
};

