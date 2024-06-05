#pragma once

#include "GameObject.h"
#include "PostEffect/IPostEffect/IPostEffect.h"


/* TestPostEffectクラス */
class TestPostEffect : public IPostEffect {

public:

	// コンストラクタ、デストラクタ
	TestPostEffect() {};
	~TestPostEffect() {};

	// 初期化処理、更新処理、描画処理
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:


};

