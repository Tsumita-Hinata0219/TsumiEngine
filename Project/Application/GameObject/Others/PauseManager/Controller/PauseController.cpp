#include "PauseController.h"
#include "../PauseManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void PauseController::Init()
{
	// 入力クラスのインスタンス取得
	input_ = Input::GetInstance();



}


/// <summary>
/// 更新処理
/// </summary>
void PauseController::Update()
{
	// ポーズ中でない場合にスタートボタンを押したらポーズ中にする
	if (m_pauseManager_->GetPauseState() == PauseState::UnPause)
	{
		if (input_->Trigger(PadData::START)) {
			m_pauseManager_->InPause();
		}
	}

	// ポーズ中の場合にスタートボタンを押したらポーズ解除中にする
	if (m_pauseManager_->GetPauseState() == PauseState::Pause)
	{
		if (input_->Trigger(PadData::START)) {
			m_pauseManager_->OutPause();
		}
	}


}
