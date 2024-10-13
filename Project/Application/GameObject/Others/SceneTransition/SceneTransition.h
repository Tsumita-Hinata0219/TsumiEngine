#pragma once

#include <list>
#include <memory>

#include "../../GameObject.h"



/* SceneTransitionクラス */
class SceneTransition {

private: // シングルトン

	// コンストラクタ、デストラクタ
	SceneTransition() = default;
	~SceneTransition() = default;
	SceneTransition(const SceneTransition&) = delete;
	const SceneTransition& operator=(const SceneTransition&) = delete;


public:

	// インスタンス取得
	static SceneTransition* GetInstance() {
		static SceneTransition instance;
		return &instance;
	}

	// 初期化、更新、描画
	void Init();
	void Update();
	void Draw2DFront();


private:

	// ImGuiの描画
	void DrawImGui();


private:

	// スプライト
	std::unique_ptr<Sprite> sprite_;
	// トランスフォーム
	Transform trans_{};
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

};

