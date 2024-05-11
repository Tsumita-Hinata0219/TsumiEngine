#pragma once

#include "MyMath.h"
#include "DescriptorManager.h"
#include "CreateResource.h"
#include "PostEffectGraphicPipeline.h"


/* PostEffectクラス */
class PostEffect {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	PostEffect() {};
	~PostEffect() {};

	// 初期化処理、描画処理
	void Initialize();
	void Draw();


private: // メンバ関数

	// コマンドコール
	void CommandCall();

private:

	// リソース
	ResourcePeroperty resource_{};

	// SRV
	uint32_t srv_ = 0;

	// 座標
	Vector2 pos_{};

	// サイズ
	Vector2 size_ = { WinApp::kWindowWidth, WinApp::kWindowHeight };
};

