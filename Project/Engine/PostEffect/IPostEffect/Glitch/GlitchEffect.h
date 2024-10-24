#pragma once

#include "../IPostEffect.h"

/* GlitchEffectクラス */
class GlitchEffect : public IPostEffect<GlitchMtl> {

public:

	// コンストラクタ、デストラクタ
	GlitchEffect() {};
	~GlitchEffect() {};

	// 初期化処理、描画処理
	void Init() override;
	void Draw() override;

	// Imguiの描画
	void DrawImGui(std::string name = "") override;

protected:

	// コマンドコール
	void CommandCall() override;
};

