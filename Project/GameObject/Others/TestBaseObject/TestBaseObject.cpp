#include "TestBaseObject.h"



// 初期化
void TestBaseObject::Init()
{
	// ModelManagerのインスタンスの取得
	modelManager_ = ModelManager::Getinstance();
	modelManager_->LoadModel("Test", "Test.obj");
	model_ = modelManager_->GetModel("Test");

	transform_.Initialize();
}


// 更新
void TestBaseObject::Update()
{


}


// 描画
void TestBaseObject::Draw3D()
{

}
void TestBaseObject::Draw2DFront()
{

}
void TestBaseObject::Draw2DBack()
{

}