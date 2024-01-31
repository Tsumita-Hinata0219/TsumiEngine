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
	spritePos_ = WinApp::WindowSize() / 4;
	spritePos_ -= (size_ / 4.0f);
	st_.translate = spritePos_;

	move_ = Vector3::zero;

	velocity_ = Vector3::zero;
}


// 更新処理
void PlayerReticle::Update(ViewProjection view)
{
	// レティクルの計算
	offsetVec_ = Vector3::oneZ;
	offsetVec_ = TransformNormal(offsetVec_, player_->GetWorldTransform().matWorld);
	offsetVec_ = Normalize(offsetVec_) * kDistReticle_;

	// 座標を入れる
	Vector3 pos = player_->GetWorldPosition();
	wt_.translate = offsetVec_ + pos;

	// 3D -> 2D へ
	RStick_ = GamePadInput::GetRStick();
	Vector2 vel = { RStick_.x, RStick_.y };
	spritePos_.x = vel.x * 10.0f + spritePos_.x;
	spritePos_.y = vel.y * -10.0f + spritePos_.y;
	st_.translate = spritePos_;
	st_.translate -= (size_ / 4.0f);


	// スクリーン座標
	float diff = 2.0f;
	Vector3 Near = Vector3(spritePos_.x * diff, spritePos_.y * diff, 0.0f);
	Vector3 Far = Vector3(spritePos_.x * diff, spritePos_.y * diff, 1.0f);

	Near = TransformByMatrix(Near, view.matInverseVPV);
	Far = TransformByMatrix(Far, view.matInverseVPV);

	Vector3 direction = Near - Far;
	direction = Normalize(direction);	
	float distobj = -50.0f;

	wt_.translate = Near + direction * distobj;

	// ワールド座標の更新
	wt_.UpdateMatrix();
	wt_.TransferMatrix();
	st_.UpdateMatrix();

#ifdef _DEBUG

	if (ImGui::TreeNode("PlayerReticle"))
	{
		ImGui::DragFloat3("Rotate", &wt_.rotate.x, 0.01f);
		ImGui::DragFloat3("3D_Translate", &wt_.translate.x, 0.01f);
		ImGui::DragFloat2("2D_Translate", &st_.translate.x, 0.01f);
		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void PlayerReticle::Draw3D(ViewProjection view)
{
	model_->Draw(wt_, view);
}

void PlayerReticle::Draw2D(ViewProjection view)
{
	sprite_->Draw(reticleTexHD_, st_, view);
}
