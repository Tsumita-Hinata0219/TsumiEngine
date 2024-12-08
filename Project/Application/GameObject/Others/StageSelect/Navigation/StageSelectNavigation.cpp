#include "StageSelectNavigation.h"
#include "../Manager/StageSelectManager.h"
#include "../Operation/StageSelectOperation.h"


/// <summary>
/// 初期化処理
/// </summary>
void StageSelectNavigation::Init()
{
	// スプライト配列のresize
	sprites_.resize(StageSelectManager::kMaxStage);
	Vector2 initSize = { 0.0f, 0.0f };
	for (auto& element : sprites_) {
		element = std::make_unique<Sprite>();
		element->Initn();
	}

	trans_.Init();
}


/// <summary>
/// 更新処理
/// </summary>
void StageSelectNavigation::Update()
{
}


/// <summary>
/// 描画処理
/// </summary>
void StageSelectNavigation::Draw2DFront()
{
	// 選択されているステージ番号だけ描画
	sprites_[pOperation_->GetSelectNum()]->Draw(trans_);
}
