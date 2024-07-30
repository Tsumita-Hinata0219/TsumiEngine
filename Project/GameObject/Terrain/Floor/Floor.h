#pragma once

#include "../../IObject/IObject.h"
#include "../../GameObject.h"


/* Floorクラス */
class Floor : public IObject {

public:

	// コンストラクタ、デストラクタ
	Floor() {};
	~Floor() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;


private:

	// モデル
	std::unique_ptr<Model> model_;

	// ワールドトランスフォーム
	Transform trans_{};
};

