#include "EnemyShield.h"



/// <summary>
/// 初期化処理
/// </summary>
void EnemyShield::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Enemys/Shield", "Shield.obj");
	model_ = modelManager_->GetModel("Shield");
	model_->SetCullMode(CullingMode::None);

	// カラーの初期設定
	color_ = Vector4::one;
	color_.w = 0.5f;

	// BodyTransfromの初期化
	trans_.Init();

	// Colliderの初期化
	sphere_ = std::make_unique<SphereCollider>(this);
	sphere_->data_.center = trans_.GetWorldPos();
	sphere_->data_.radius = 1.8f;

}


/// <summary>
/// 更新処理
/// </summary>
void EnemyShield::Update()
{
	sphere_->data_.center = trans_.GetWorldPos();

#ifdef _DEBUG
	DrawImGui();
#endif // _DEBUG

}


/// <summary>
/// 更新処理
/// </summary>
void EnemyShield::Draw3D()
{
	// BodyModelの描画
	model_->SetMaterialColor(color_);
	model_->Draw(trans_);
}
void EnemyShield::Draw2DFront()
{
}
void EnemyShield::Draw2DBack()
{
}


/// <summary>
/// 衝突判定コールバック関数
/// </summary>
void EnemyShield::onCollision([[maybe_unused]]IObject* object)
{
}


/// <summary>
/// DrawImGuiの描画
/// </summary>
void EnemyShield::DrawImGui()
{
	if (ImGui::TreeNode("EnemyShield")) {

		trans_.DrawImGui();
		ImGui::Text("");

		ImGui::ColorEdit4("Color", &color_.x);
		ImGui::Text("");

		ImGui::TreePop();
	}
}
