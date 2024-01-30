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

	// テクスチャサイズ
	size_ = { 64.0f, 64.0f };

	// スプライトの初期化
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(Vector2::zero, size_);

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

	// 座標を入れる
	wt_.translate = offsetVec_;

	// 3D -> 2D へ
	st_.translate = (ConvertVector(wt_.GetWorldPos(), view) / 2.0f);
	st_.translate -= (size_ / 4.0f);


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
void PlayerReticle::Draw3D(ViewProjection view)
{
	view;//model_->Draw(wt_, view);
}

void PlayerReticle::Draw2D(ViewProjection view)
{
	sprite_->Draw(reticleTexHD_, st_, view);
}
