#pragma once

#include "../../../../IObject/IObject.h"
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
