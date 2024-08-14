#include "StaticEnemy.h"
#include "../../../Player/Player.h"



// 初期化処理
void StaticEnemy::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Enemys/Static", "Static.obj");
	model_ = modelManager_->GetModel("Static");

	// BodyTransfromの初期化
	trans_.Init();

	// Colliderの初期化
	collider_ = std::make_unique<OBBCollider>();
	collider_->Init();
	collider_->SetSize(size_);

	// 回転スピード(ラジアン)
	addRadSpeed_ = 1.0f;
}


// 更新処理
void StaticEnemy::Update()
{
	// 回転
	trans_.srt.rotate.y += ToRadians(addRadSpeed_);


#ifdef _DEBUG

#endif // _DEBUG
}


// 描画処理
void StaticEnemy::Draw3D()
{
	// BodyModelの描画
	model_->DrawN(trans_);
}
void StaticEnemy::Draw2DFront() {}
void StaticEnemy::Draw2DBack() {}

