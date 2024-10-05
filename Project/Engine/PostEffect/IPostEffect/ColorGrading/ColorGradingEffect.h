#pragma once

#include "../IPostEffect.h"

/* ColorGradingEffectクラス */
class ColorGradingEffect : public IPostEffect<ColorGradingMtl> {

public:

	// コンストラクタ、デストラクタ
	ColorGradingEffect() {};
	~ColorGradingEffect() {};

	// 初期化処理、描画処理
	void Init() override;
	void Draw() override;

	// Imguiの描画
	void DrawImGui(std::string name = "") override;

protected:

	// コマンドコール
	void CommandCall() override;
};
