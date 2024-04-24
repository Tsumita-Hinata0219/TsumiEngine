#include "TestAnimationCube.h"



// 初期化処理
void TestAnimationCube::Init()
{
	testModel_ = make_unique<Model>();
	testModel_->CreateGLTFModel("", "AnimatedCube");
	testAnimation_ = AnimationManager::LoadAnimationFile("", "AnimatedCube");

	wt_.Initialize();
}


// 更新処理
void TestAnimationCube::Update()
{
	wt_.UpdateMatrix();
	testModel_->PlayAnimation(testAnimation_, animationtime);

#ifdef _DEBUG

	if (ImGui::TreeNode("TestAnimationCube")) {

		ImGui::DragFloat3("Scale", &wt_.scale.x, 0.1f);
		ImGui::DragFloat3("Rotate", &wt_.rotate.x, 0.1f);
		ImGui::DragFloat3("Translate", &wt_.translate.x, 0.1f);

		ImGui::Text("");
		ImGui::DragFloat("Animationtime", &animationtime, 0.01f, 0.0f, 10.f);

		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void TestAnimationCube::Draw(Camera* camera)
{
	testModel_->Draw(wt_, camera);
}

