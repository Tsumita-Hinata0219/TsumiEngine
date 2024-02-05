#include "Cloud.h"



// 初期化処理
void Cloud::Initialize()
{
	// テクスチャの読み込み
	cloudTexHD_ = TextureManager::LoadTexture("cloud.png");

	// スプライトの初期化
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(Vector2::zero, { 1280.0f, 720.0f });

	// ワールドトランスフォームの初期化
	wt_.Initialize();
}


// 更新処理
void Cloud::Update()
{
	wt_.UpdateMatrix();

}


// 描画処理
void Cloud::Draw(ViewProjection view)
{
	sprite_->Draw(cloudTexHD_, wt_, view);	
}
