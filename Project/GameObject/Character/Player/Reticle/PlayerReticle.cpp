#include "PlayerReticle.h"
#include "Player/Player.h"



// 初期化処理
void PlayerReticle::Initialize(Model& modelHD, Vector3 initTranslate)
{
	// モデルの初期化
	model_ = make_unique<Model>();
	(*model_) = modelHD;

	// テクスチャの読み込み
	reticleTexHD_ = TextureManager::LoadTexture("PlayerReticle.png");

	// スプライトの初期化
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize({ initTranslate.x, initTranslate.y }, { 128.0f, 128.0f });

	// ワールドトランスフォームの初期化
	wt_.Initialize();
	wt_.translate = initTranslate;

	// オフセット
	offsetVec_ = Vector3::oneZ;
}


// 更新処理
void PlayerReticle::Update()
{
	// ワールド座標の更新
	wt_.UpdateMatrix();


	if (KeyInput::PressKeys(DIK_LEFT)) {
		wt_.translate.x -= 0.3f;
	}
	if (KeyInput::PressKeys(DIK_RIGHT)) {
		wt_.translate.x += 0.3f;
	}
}


// 描画処理
void PlayerReticle::Draw(ViewProjection view)
{
	sprite_->Draw(reticleTexHD_, wt_, view);
}
