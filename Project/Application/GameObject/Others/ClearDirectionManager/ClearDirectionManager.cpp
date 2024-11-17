#include "ClearDirectionManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void ClearDirectionManager::Init()
{
	/* ----- BackScreen 背景スクリーン ----- */
	backScreen_ = std::make_unique<ClearDirectionBackScreen>();
	backScreen_->Init();

	/* ----- Liner ライナー ----- */
	liner_ = std::make_unique<ClearDirectionLiner>();
	liner_->Init();

	/* ----- Moji 文字 ----- */
	moji_ = std::make_unique<ClearDirectionMoji>();
	moji_->Init();

}


/// <summary>
/// 更新処理
/// </summary>
void ClearDirectionManager::Update()
{
	/* ----- BackScreen 背景スクリーン ----- */
	backScreen_->Update();

	/* ----- Liner ライナー ----- */
	liner_->Update();

	/* ----- Moji 文字 ----- */
	moji_->Update();
}


/// <summary>
/// 描画処理
/// </summary>
void ClearDirectionManager::Draw2DFront()
{
	/* ----- BackScreen 背景スクリーン ----- */
	backScreen_->Draw2DFront();

	/* ----- Liner ライナー ----- */
	liner_->Draw2DFront();

	/* ----- Moji 文字 ----- */
	moji_->Draw2DFront();

}

