#pragma once

#include "GameObject/GameObject.h"

#include "Controller/PauseController.h"
#include "Renderer/PauseRenderer.h"


enum class PauseState {
	// ポーズ中
	Pause,
	// ポーズ処理中
	Pausing,
	// ポーズ解除処理中
	UnPausing,
	// ポーズ解除中
	UnPause,
};


/* ポーズ処理マネージャー */
class PauseManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PauseManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PauseManager() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw2DFront();
	void Draw2DBack();

	/// <summary>
	/// ポーズをかける
	/// </summary>
	void InPause();

	/// <summary>
	/// ポーズを解除する
	/// </summary>
	void OutPause();

#pragma region Accessor

	// ポーズ中かどうか
	bool IsPause() const { return m_isPause_; }

	// ポーズ処理ステート
	PauseState GetPauseState() const { return m_pauseState_; }

#pragma endregion 


private:

	/// <summary>
	/// ポーズ処理
	/// </summary>
	void FuncPause();

	/// <summary>
	/// ポーズ解除処理
	/// </summary>
	void FuncUnPause();


private:

	// ポーズ中かどうか
	bool m_isPause_ = false;

	// ポーズ処理ステート
	PauseState m_pauseState_ = PauseState::Pause;

	// 操作クラス
	std::unique_ptr<PauseController> m_pauseController_ = nullptr;
	// 描画クラス
	std::unique_ptr<PauseRenderer> m_pauseRenderer_ = nullptr;

	// タイマー
	Timer m_funcTimer_;
};
