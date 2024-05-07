#pragma once

#include "MyMath.h"
#include "DescriptorManager.h"
#include "CreateResource.h"


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

	// 頂点データの設定
	void SetVertex();

	// コマンドコール
	void CommandCall();

private:

	// リソース
	ResourcePeroperty resource_{};

	// SRV
	uint32_t srv_;
};

