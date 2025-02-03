#include "PauseRenderer.h"
#include "../PauseManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void PauseRenderer::Init()
{
	// テクスチャハンドル
	uint32_t backTexHD = TextureManager::LoadTexture("Texture/Game/Pause", "Pause_Back.png");


	// Back
	m_BackSprite_ = std::make_unique<Sprite>();
	m_BackSprite_->Init({ 1280.0f, 720.0f });
	m_BackSprite_->SetTexture(backTexHD);
	m_BackSprite_->SetAnchor(SpriteAnchor::TopLeft);
	m_BackTransform_.Init();
	// 初期カラーとターゲットカラー
	m_BackUnPauseAlpha_ = 0.0f;
	m_BackPauseAlpha_ = 0.8f;
	m_BackColor_ = Temp::Color::BLACK;
	m_BackColor_.w = m_BackUnPauseAlpha_;






}


/// <summary>
/// 更新処理
/// </summary>
void PauseRenderer::Update()
{
	// ポーズ処理中でなければ早期return
	if (!m_pauseManager_->IsPause()) {
		return;
	}

	// Back
	CalcBackAlpha();

}


/// <summary>
/// 描画処理
/// </summary>
void PauseRenderer::Draw2DFront()
{
	// ポーズじゃない時は通らない
	if (m_pauseManager_->GetPauseState() == PauseState::UnPause) {
		return;
	}

	// Back
	m_BackSprite_->SetColor(m_BackColor_);
	m_BackSprite_->Draw(m_BackTransform_);

}


/// <summary>
/// ポーズをかける
/// </summary>
void PauseRenderer::InPause()
{
	// BackのAlphaの設定
	m_BackCalcAlpha_ = { m_BackUnPauseAlpha_, m_BackPauseAlpha_ };
}


/// <summary>
/// ポーズを解除する
/// </summary>
void PauseRenderer::OutPause()
{
	// BackのAlphaの設定
	m_BackCalcAlpha_ = { m_BackPauseAlpha_, m_BackUnPauseAlpha_ };
}


/// <summary>
/// BackのAlphaの計算
/// </summary>
void PauseRenderer::CalcBackAlpha()
{
	m_BackColor_.w = Interpolate(
		m_BackCalcAlpha_.first, m_BackCalcAlpha_.second,
		m_pauseManager_->GetFuncTimer().GetRatio(), Ease::OutSine);
}
