#include "StartDirection.h"



// 初期化処理
void StartDirection::Init()
{
	// テクスチャの読み込み
	textures_.resize(4);
	textures_ = {
		TextureManager::LoadTexture("Texture", "monsterBall.png"),
		TextureManager::LoadTexture("Texture", "monsterBall.png"),
		TextureManager::LoadTexture("Texture", "monsterBall.png"),
		TextureManager::LoadTexture("Texture", "monsterBall.png"),
	};
	texArrayNum_ = 0;

	// スプライト
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initn();
	sprite_->SetTexture(textures_[texArrayNum_]);
	sprite_->SetAnchor(SpriteAnchor::Center); // 中心原点

	// トランスフォーム
	trans_.Init();
	trans_.srt.translate = {
		WinApp::kHalfWindowWidth,
		WinApp::kHalfWindowHeight,
		0.0f,
	};
}


// 更新処理
void StartDirection::Update()
{
	// サイズの移行処理
	SizeFunc();

	// 姿勢の移行処理
	RotateFunc();
}


// 描画処理
void StartDirection::Draw2DFront()
{
	sprite_->Draw(trans_);
}


// サイズの移行処理
void StartDirection::SizeFunc()
{
}


// 姿勢の移行処理
void StartDirection::RotateFunc()
{
}


