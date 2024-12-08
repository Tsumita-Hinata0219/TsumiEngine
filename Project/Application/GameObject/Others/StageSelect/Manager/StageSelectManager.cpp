#include "StageSelectManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void StageSelectManager::Init()
{
	// 操作クラス
	operation_ = std::make_unique<StageSelectOperation>();
	operation_->Init();

	// ナビゲーション
	navigation_ = std::make_unique<StageSelectNavigation>();
	navigation_->Init();
	navigation_->SetOperation(operation_.get());
}


/// <summary>
/// 更新処理
/// </summary>
void StageSelectManager::Update()
{
	// 操作クラス
	operation_->Update();
}


/// <summary>
/// 描画処理
/// </summary>
void StageSelectManager::Draw2DFront()
{
	navigation_->Draw2DFront();
}

	