#include "TitleLabelObject.h"



// 初期化処理
void TitleLabelObject::Init()
{
	// Modelの設定
	modelManager_ = ModelManager::GetInstance();
	model_ = modelManager_->GetModel("Player_Center_Body");

	// Transformの初期化
	trans_.Init();

}


// 更新処理
void TitleLabelObject::Update() {}


// 描画処理
void TitleLabelObject::Draw3D()
{
	model_->DrawN(trans_);
}
void TitleLabelObject::Draw2DFront() {}
void TitleLabelObject::Draw2DBack() {}


// 衝突判定コールバック関数
void TitleLabelObject::onCollision([[maybe_unused]] IObject* object)
{
}
