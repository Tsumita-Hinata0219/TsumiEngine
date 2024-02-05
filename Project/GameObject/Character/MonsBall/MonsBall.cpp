#include "MonsBall.h"



// 初期化処理
void MonsBall::Initialize()
{
	// ノーマルマップ用テクスチャの読み込み
	normalMapTexHD_ = TextureManager::LoadTexture("normalMap.png");

	// モデルの初期化
	monsBall_ = make_unique<Model>();
	monsBall_->CreateFromObj("ball");

	// ワールドトランスフォームの初期化
	wt_.Initialize();

}


// 更新処理
void MonsBall::Update()
{



}


// 描画処理
void MonsBall::Draw(ViewProjection view)
{



}
