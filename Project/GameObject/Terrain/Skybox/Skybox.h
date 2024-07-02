#pragma once

#include "../../Tsumi/CommandManager/CommandManager.h"
#include "../../Tsumi/CreateResource/CreateResource.h"
#include "../../Tsumi/PipeLineManager/PipeLineManager.h"

#include "../../GameObject.h"


/* Skyboxクラス */
class Skybox {

private: // シングルトンデザインパターン

	// コンストラクタ、デストラクタ
	Skybox() = default;
	~Skybox() = default;
	Skybox(const Skybox&) = delete;
	const Skybox& operator=(const Skybox&) = delete;


public: // メンバ関数

	// インスタンスの取得
	static Skybox* GetInstance() {
		static Skybox instance;
		return &instance;
	}

	// 初期化処理、更新処理、描画処理
	void Initialize();
	void Update();
	void Draw(Camera* camera);


private:

	// コマンドコール
	void CommandCall(Camera* camera);


private: // メンバ変数

	// 使用するTextureHandle
	uint32_t texture_ = 0;

	// リソース
	ResourcePeroperty resource_{};

};

