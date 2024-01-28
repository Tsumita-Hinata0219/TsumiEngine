#include "PlayerReticle.h"
#include "Player/Player.h"



// 初期化処理
void PlayerReticle::Initialize(Model& modelHD, Vector3 initTranslate)
{
	// モデルの初期化
	model_ = make_unique<Model>();
	(*model_) = modelHD;
	// ワールドトランスフォームの初期化
	wt_.Initialize();
	wt_.translate = initTranslate;
	// オフセット
	offsetVec_ = Vector3::oneZ;

	// テクスチャの読み込み
	reticleTexHD_ = TextureManager::LoadTexture("PlayerReticle.png");

	// スプライトの初期化
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(Vector2::zero, { 64.0f, 64.0f });

	// スプライトトランスフォームの初期化
	st_.Initialize();
}


// 更新処理
void PlayerReticle::Update(ViewProjection view)
{
	// ワールド座標の更新
	wt_.UpdateMatrix();
	st_.UpdateMatrix();


	// レティクルの計算
	offsetVec_ = Vector3::oneZ;
	offsetVec_ = TransformNormal(offsetVec_, player_->GetWorldTransform().matWorld);
	offsetVec_ = Normalize(offsetVec_) * kDistReticle_;
	offsetVec_ += player_->GetWorldPosition();

	// 座標を入れる
	wt_.translate = offsetVec_;

	// 3D -> 2D へ
	st_.translate = (ConvertVector(wt_.GetWorldPos(), view) / 2.0f);
	Vector2 size = { 32.0f, 32.0f };
	st_.translate.x -= (size.x / 2.0f);


	/*if (KeyInput::PressKeys(DIK_LEFT)) {
		wt_.translate.x -= 0.3f;
	}
	if (KeyInput::PressKeys(DIK_RIGHT)) {
		wt_.translate.x += 0.3f;
	}*/


#ifdef _DEBUG

	if (ImGui::TreeNode("PlayerReticle"))
	{
		ImGui::DragFloat3("Rotate", &wt_.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &wt_.translate.x, 0.01f);
		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void PlayerReticle::Draw(ViewProjection view)
{
	//model_->Draw(wt_, view);
	sprite_->Draw(reticleTexHD_, st_, view);
}
