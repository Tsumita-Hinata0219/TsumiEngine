#include "ClearDirectionManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void ClearDirectionManager::Init()
{
	/* ----- BackScreen 背景スクリーン ----- */
	backScreen_ = std::make_unique<ClearDirectionBackScreen>();
	backScreen_->Init();


}


/// <summary>
/// 更新処理
/// </summary>
void ClearDirectionManager::Update()
{
	/* ----- BackScreen 背景スクリーン ----- */
	backScreen_->Update();
}


/// <summary>
/// 描画処理
/// </summary>
void ClearDirectionManager::Draw2DFront()
{
	/* ----- BackScreen 背景スクリーン ----- */
	backScreen_->Draw2DFront();
}

