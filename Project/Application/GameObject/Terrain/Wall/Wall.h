#pragma once

#include "GameObject/IObject/IObject.h"
#include "GameObject/GameObject.h"

#include "JsonManager/JsonManager.h"


/* Wallクラス */
class Wall : public IObject {

public:

	// コンストラクタ、デストラクタ
	Wall() {};
	~Wall() {};

	// 初期化処理、更新処理、描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	// 衝突判定コールバック関数
	void onCollision([[maybe_unused]] IObject* object) override;


private:

	// モデル
	std::unique_ptr<Model> model_;

	// ワールドトランスフォーム
	Transform trans_{};
};
