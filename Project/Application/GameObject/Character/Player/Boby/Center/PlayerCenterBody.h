#pragma once

#include "../../../../IObject/IObject.h"
#include "../IPlayerBody.h"



/* プレイヤーのCenterBodyクラス */
class PlayerCenterBody : public IPlayerBody {

public:

	// コンストラクタ、デストラクタ
	PlayerCenterBody() {};
	~PlayerCenterBody() {};

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

#pragma endregion 


private:

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};

	// ライト
	DirectionalLightData light_{};
};
