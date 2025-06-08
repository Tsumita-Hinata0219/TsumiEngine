#pragma once

#include "System/IObject/IObject.h"
#include "../IPlayerBody.h"



/* プレイヤーのRightBodyクラス */
class PlayerRightBody : public IPlayerBody {

public:

	// コンストラクタ、デストラクタ
	PlayerRightBody() {};
	~PlayerRightBody() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	// 衝突判定コールバック関数
	void onCollision([[maybe_unused]] IObject* object) override;


#pragma region Accessor アクセッサ

	// ペアレント
	void SetParent(Transform* parent) override { this->trans_.SetParent(parent); }

	// モデルのカラーの設定
	void SetModelColor(const Vector4& setColor) override { this->model_->SetMaterialColor(setColor); }

	// モデルのライトの設定
	void SetModelLight(const DirectionalLightData& setLight) override { this->model_->SetLightData(setLight); }

#pragma endregion 


private:

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};
};

