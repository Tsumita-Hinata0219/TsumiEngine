#include "Wall.h"



// 初期化処理
void Wall::Init()
{
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Wall", "Wall.obj");
	model_ = modelManager_->GetModel("Wall");

	JsonManager* jsonManager = JsonManager::GetInstance();

	trans_.Initialize();
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
