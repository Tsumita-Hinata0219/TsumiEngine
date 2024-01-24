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
}


// 更新処理
void PlayerReticle::Update()
{
	// レティクルの計算
	offsetVec_ = Vector3::oneZ;
	offsetVec_ = TransformNormal(offsetVec_, player_->GetWorldTransform().matWorld);
	offsetVec_ = Normalize(offsetVec_) * kDistReticle_;
	offsetVec_ += player_->GetWorldPosition();

	// 座標を入れる
	wt_.translate = offsetVec_;

	// ワールド座標の更新
	wt_.UpdateMatrix();


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
	model_->Draw(wt_, view);
}
