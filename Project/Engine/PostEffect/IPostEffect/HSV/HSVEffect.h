#pragma once

#include "../IPostEffect.h"

/* HSVEffectクラス */
class HSVEffect : public IPostEffect<HSVMtl> {

public:

	// コンストラクタ、デストラクタ
	HSVEffect() {};
	~HSVEffect() {};

	// 初期化処理、描画処理
	void Initialize() override;
	void Draw() override;

	// Imguiの描画
	void DrawImGui(std::string name = "") override;

protected:

	// コマンドコール
	void CommandCall() override;
};

