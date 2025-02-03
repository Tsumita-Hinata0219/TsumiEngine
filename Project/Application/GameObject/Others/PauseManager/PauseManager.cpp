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
	}
}
