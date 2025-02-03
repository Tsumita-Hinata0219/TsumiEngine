#include "PauseManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void PauseManager::Init()
{
	// 操作クラス
	m_pauseController_ = std::make_unique<PauseController>(this);
	m_pauseController_->Init();

	// 描画クラス                        PuaseRenderer
	m_pauseRenderer_ = std::make_unique<PauseRenderer>(this);
	m_pauseRenderer_->Init();

	// タイマーの設定
	m_funcTimer_.Init(0.0f, 0.5f * 60.0f);



	// フラグは折っておく
	m_isPause_ = false;

	// ポーズステートはポーズ解除中
	m_pauseState_ = PauseState::UnPause;
}


/// <summary>
/// 更新処理
/// </summary>
void PauseManager::Update()
{
}


/// <summary>
/// 描画処理
/// </summary>
void PauseManager::Draw2DFront()
{
}
void PauseManager::Draw2DBack()
{
}


/// <summary>
/// ポーズをかける
/// </summary>
void PauseManager::InPause()
{
	if (m_pauseState_ == PauseState::UnPause)
	{
		// ポーズ中にする
		m_pauseState_ = PauseState::Pausing;
		// タイマースタート
		m_funcTimer_.Start();
	}
}


/// <summary>
/// ポーズを解除する
/// </summary>
void PauseManager::OutPause()
{
	if (m_pauseState_ == PauseState::Pause)
	{
		// ポーズ解除中にする
		m_pauseState_ = PauseState::UnPausing;
		// タイマースタート
		m_funcTimer_.Start();
	}
}


/// <summary>
/// ポーズ処理
/// </summary>
void PauseManager::FuncPause()
{
	if (m_pauseState_ == PauseState::Pausing)
	{
		// タイマー更新
		m_funcTimer_.Update();
		// タイマー終了
		if (m_funcTimer_.IsFinish())
		{
			// ポーズ中にする
			m_pauseState_ = PauseState::Pause;
			// タイマーリセット
			m_funcTimer_.Clear();
		}
	}
}


/// <summary>
/// ポーズ解除処理
/// </summary>
void PauseManager::FuncUnPause()
{
	if (m_pauseState_ == PauseState::UnPausing)
	{
		// タイマー更新
		m_funcTimer_.Update();
		// タイマー終了
		if (m_funcTimer_.IsFinish())
		{
			// ポーズ中にする
			m_pauseState_ = PauseState::UnPause;
			// タイマーリセット
			m_funcTimer_.Clear();
		}
	}
}
