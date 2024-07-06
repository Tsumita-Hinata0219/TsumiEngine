#pragma once

#include "../../GameObject.h"
#include "../../../Tsumi/PostEffect/IPostEffect/IPostEffect.h"

#include "../../Tsumi/PostEffect/IPostEffect/BoxFilter/BoxFilterEffect.h"


/* TestPostEffectクラス */
class TestPostEffect{

public:

	// コンストラクタ、デストラクタ
	TestPostEffect() {};
	~TestPostEffect() {};

	// 初期化処理、更新処理、描画処理
	void Initialize();
	void Update();
	void Draw(Camera* camera);

private:

	std::unique_ptr<BoxFilterEffect> boxFilter_;

};

