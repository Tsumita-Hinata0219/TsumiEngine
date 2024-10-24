#pragma once

#include "../../IObject/IObject.h"

/* TestBaseObjectクラス */
class TestBaseObject : public IObject {

public:

	// コンストラクタ、デストラクタ
	TestBaseObject() {};
	~TestBaseObject() {};

	// 初期化、更新、描画
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

private:

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};
};

