#include "TestObject.h"



// 初期化処理
void TestObject::Init()
{
	testModel_ = make_unique<Model>();
	testModel_->CreateGLTFModel("GLTFPlane");

	wt_.Initialize();
}


// 更新処理
void TestObject::Update()
{
	wt_.UpdateMatrix();

#ifdef _DEBUG

	if (ImGui::TreeNode("TestObject")) {

		ImGui::DragFloat3("Scale", &wt_.scale.x, 0.1f);
		ImGui::DragFloat3("Rotate", &wt_.rotate.x, 0.1f);
		ImGui::DragFloat3("Translate", &wt_.translate.x, 0.1f);

		ImGui::TreePop();
	}

#endif // _DEBUG


}


// 描画処理
void TestObject::Draw(Camera* camera)
{
	testModel_->Draw(wt_, camera);
}
