#pragma once

#include <list>
#include <memory>

#include "../../GameObject.h"



// TransitionState
enum TransitionState {
	Opened,
	Cloased,
	Opening,
	Closing,
};


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
	void Init(TransitionState state);
	void Update();
	void Draw2DFront();

	// フェードイン開始
	void StartFadeIn();

	// フェードアウト開始
	void StartFadeOut();


#pragma region Accessor アクセッサ


#pragma endregion


private:

	// 遷移処理
	void FuncTransition();

	// ImGuiの描画
	void DrawImGui();


private:

	// スプライト
	std::unique_ptr<Sprite> sprite_;
	// トランスフォーム
	Transform trans_{};
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// SpriteDissolve
	SP::DissolveData dissolve_{};

	// 現在のステート
	TransitionState nowState_ = Opened;

	// トランジションにかかる時間
	Timer transitionTimer_{};
	float transitionDuration_ = 0.0f;

	// 開始Dissolve進行度
	float startThreshold_ = 0.0f;
	// 目標Dissolve進行度
	float targetThreshold_ = 0.0f;
};

