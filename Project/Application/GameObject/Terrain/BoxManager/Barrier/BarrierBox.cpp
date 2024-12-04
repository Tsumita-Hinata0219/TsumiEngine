#include "BarrierBox.h"



/// <summary>
/// 初期化処理
/// </summary>
void BarrierBox::Init()
{
	// モデルのロードと初期化
	modelManager_->LoadModel("Obj/Boxs/BarrierBox", "BarrierBox.obj");
	model_ = modelManager_->GetModel("BarrierBox");

	// ライトの初期設定
	light_.enable = true;
	light_.direction = Vector3::one;
	light_.intensity = 0.7f;
	model_->SetLightData(light_);

	// トランスフォームの初期化
	trans_.Init();

	//// コライダーの初期化
	//colComp_->SetAttribute(ColliderAttribute::Terrain);
	///*colComp_->Register(sphere_);
	//sphere_.center = trans_.GetWorldPos();
	//sphere_.radius = 2.0f;*/
	//colComp_->Register(aabb_);
	//aabb_.center = trans_.GetWorldPos();
	//aabb_.max = { 2.0f, 2.0f, 2.0f };
	//aabb_.min = { -2.0f, -2.0f, -2.0f };
}


/// <summary>
/// 更新処理
/// </summary>
void BarrierBox::Update()
{
	/*sphere_.center = trans_.GetWorldPos();
	aabb_.center = trans_.GetWorldPos();*/
}


/// <summary>
/// 描画処理
/// </summary>
void BarrierBox::Draw3D()
{
	model_->DrawN(trans_);
}
void BarrierBox::Draw2DFront()
{
}
void BarrierBox::Draw2DBack()
{
}


/// <summary>
/// 衝突判定コールバック関数
/// </summary>
void BarrierBox::onCollision([[maybe_unused]] IObject* object)
{
}
