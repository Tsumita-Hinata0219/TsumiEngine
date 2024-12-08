#include "StageSelectManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void StageSelectManager::Init()
{
	
	// 操作クラス
	operation_ = std::make_unique<StageSelectOperation>();
	operation_->Init();
}


/// <summary>
/// 更新処理
/// </summary>
void StageSelectManager::Update()
{
	// 操作クラス
	operation_->Update();
}

	