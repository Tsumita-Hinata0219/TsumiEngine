#include "StageSelectNavigation.h"
#include "../Manager/StageSelectManager.h"
#include "../Operation/StageSelectOperation.h"


/// <summary>
/// 初期化処理
/// </summary>
void StageSelectNavigation::Init()
{
	textures_ = {
		TextureManager::LoadTexture("Texture/Select/StageNumber", "StageNum_Demo.png"),
		TextureManager::LoadTexture("Texture/Select/StageNumber", "StageNum_1.png"),
		TextureManager::LoadTexture("Texture/Select/StageNumber", "StageNum_2.png"),
		TextureManager::LoadTexture("Texture/Select/StageNumber", "StageNum_3.png"),
		TextureManager::LoadTexture("Texture/Select/StageNumber", "StageNum_4.png"),
		TextureManager::LoadTexture("Texture/Select/StageNumber", "StageNum_5.png"),
	};


	// スプライト配列のresize
	sprites_.resize(StageSelectManager::kMaxStage);
	Vector2 initSize = { 0.0f, 0.0f };
	for (int i = 0; i < StageSelectManager::kMaxStage; ++i) {
		sprites_[i] = std::make_unique<Sprite>();
		sprites_[i]->Init();
		sprites_[i]->SetTexture(textures_[i]);
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
