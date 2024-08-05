#pragma once

#include "../../Tsumi/CommandManager/CommandManager.h"
#include "../../Tsumi/CreateResource/CreateResource.h"
#include "../../Tsumi/PipeLineManager/PipeLineManager.h"

#include "../../GameObject.h"


/* Skyboxクラス */
class Skybox {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	Skybox() {};
	~Skybox() {};

	// 初期化処理、更新処理、描画処理
	void Init();
	void Update();
	void Draw();


private:

	// コマンドコール
	void CommandCall();


private: // メンバ変数

	// Transform
	WorldTransform transform_{};
	float initScale_ = 1.0f;

	// 使用するTextureHandle
	uint32_t texture_ = 0;

	// カラー
	Vector4 color_{};

	// 定数の頂点数とインデックス数
	const size_t kNumVertices_ = 24; // 各面4頂点、6面で計24頂点
	const size_t kNumIndices_ = 36;  // 各面6インデックス、6面で計36インデックス

	// リソース
	ResourcePeroperty resource_{};
};

