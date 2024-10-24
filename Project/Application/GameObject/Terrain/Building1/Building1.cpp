#include "Building1.h"



// 初期化処理
void Building1::Init()
{
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Building1", "Building1.obj");
	model_ = modelManager_->GetModel("Building1");

	JsonManager* jsonManager = JsonManager::GetInstance();

	trans_.Init();
	trans_.srt.translate =
		jsonManager->GetObjectSRT("Building").translate;
}


// 更新処理
void Building1::Update()
{
}


// 描画処理
void Building1::Draw3D()
{
	model_->DrawN(trans_);

}
void Building1::Draw2DFront() {}
void Building1::Draw2DBack() {}


// 衝突判定コールバック関数
void Building1::onCollision([[maybe_unused]] IObject* object)
{
}
