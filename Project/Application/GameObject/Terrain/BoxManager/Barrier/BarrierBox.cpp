#include "BarrierBox.h"



/// <summary>
/// 初期化処理
/// </summary>
void BarrierBox::Init()
{
	// モデルのロードと初期化
	modelManager_->LoadModel("Obj/Boxs/BarrierBox", "BarrierBox.obj");
	model_ = modelManager_->GetModel("BarrierBox");

	// トランスフォームの初期化
	trans_.Init();
}


/// <summary>
/// 更新処理
/// </summary>
void BarrierBox::Update()
{
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
