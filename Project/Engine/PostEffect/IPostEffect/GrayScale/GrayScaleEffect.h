#pragma once

#include "../IPostEffect.h"

/* GrayScaleEffectクラス */
class GrayScaleEffect : public IPostEffect<GrayScaleMtl> {

public:

	// コンストラクタ、デストラクタ
	GrayScaleEffect() {};
	~GrayScaleEffect() {};

	// 初期化処理、描画処理
	void Init() override;
	void Draw() override;

	// Imguiの描画
	void DrawImGui(std::string name = "") override;

protected:

	// コマンドコール
	void CommandCall() override;
};
