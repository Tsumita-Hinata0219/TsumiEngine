#pragma once

#include "../IPostEffect.h"

/* DissolveEffectクラス */
class DissolveEffect : public IPostEffect<DissolveMtl> {

public:

	// コンストラクタ、デストラクタ
	DissolveEffect() {};
	~DissolveEffect() {};

	// 初期化処理、描画処理
	void Init() override;
	void Draw() override;

	// Imguiの描画
	void DrawImGui(std::string name = "") override;

protected:

	// コマンドコール
	void CommandCall() override;
};
