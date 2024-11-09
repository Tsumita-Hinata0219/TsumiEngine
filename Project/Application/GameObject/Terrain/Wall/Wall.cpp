#include "Wall.h"



// 初期化処理
void Wall::Init()
{
	modelManager_ = ModelManager::GetInstance();
	model_ = modelManager_->GetModel("Wall");

	JsonManager* jsonManager = JsonManager::GetInstance();
	trans_.Init();
	trans_.srt.translate =
		jsonManager->GetObjectSRT("Wall").translate;
}


// 更新処理
void Wall::Update()
{
}


// 描画処理
void Wall::Draw3D()
{
	model_->DrawN(trans_);

}
void Wall::Draw2DFront() {}
void Wall::Draw2DBack() {}


// 衝突判定コールバック関数
void Wall::onCollision([[maybe_unused]] IObject* object, [[maybe_unused]] Col::ColData colData)
{
}
