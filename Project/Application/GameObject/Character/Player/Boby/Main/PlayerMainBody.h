#pragma once

#include "../../../../IObject/IObject.h"
#include "../IPlayerBody.h"



/* プレイヤーのMainBodyクラス */
class PlayerMainBody : public IPlayerBody {

public:

	// コンストラクタ、デストラクタ
	PlayerMainBody() {};
	~PlayerMainBody() {};

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
	void SetParent(Transform* parent) { this->trans_.SetParent(parent); }

#pragma endregion 


private:

	// モデル
	std::vector<std::unique_ptr<Model>> models_;

	// トランスフォーム
	Transform trans_{};

	// ライト
	DirectionalLightData light_{};
};
