#include "TestBaseObject.h"



// 初期化
void TestBaseObject::Init()
{
	// ModelManagerのインスタンスの取得
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Test", "Test.obj");
	model_ = modelManager_->GetModel("Test");

	trans_.Initialize();
}


// 更新
void TestBaseObject::Update()
{


}


// 描画
void TestBaseObject::Draw3D()
{
	model_->DrawN(trans_);
}
void TestBaseObject::Draw2DFront()
{

}
void TestBaseObject::Draw2DBack()
{

}
