#include "DemoCollisionScene.h"



/// <summary>
/// デストラクタ
/// </summary>
DemoCollisionScene::~DemoCollisionScene() {}



/// <summary>
/// 初期化処理
/// </summary>
void DemoCollisionScene::Initialize() {

	viewProjection_.Initialize();
	viewProjection_.translate = { 0.0f, 0.0f, -20.0f };


	// カプセルの初期化処理
	// 1
	capsuleObj1_ = make_unique<Model>();
	capsuleObj1_->CreateFromObj("Capsule");
	capsuleObj1_->SetModelDrawType(Phong);
	capsuleWt1_.Initialize();
	capsuleWt1_.translate.x = -4.0f;

	// 2
	capsuleObj2_ = make_unique<Model>();
	capsuleObj2_->CreateFromObj("Capsule");
	capsuleObj2_->SetModelDrawType(Phong);
	capsuleWt2_.Initialize();
	capsuleWt2_.translate.x = 4.0f;




	capsuleLight_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	capsuleLight_.direction = { 0.0f, 0.0f, -1.0f };
	capsuleLight_.intensity = 1.0f;
	capsuleLight_.sininess = 100.0f;
	capsuleLight_.enableLightting = true;

}



/// <summary>
/// 更新処理
/// </summary>
void DemoCollisionScene::Update(GameManager* state) {

	viewProjection_.UpdateMatrix();
	Scope s = { 0.0f, 1000.0f };
	Vector3 rand = {
			RandomGenerator::getRandom(s) * 0.001f,
			RandomGenerator::getRandom(s) * 0.001f,
			RandomGenerator::getRandom(s) * 0.001f,
	};


	// カプセルの更新処理
	// 1
	capsuleWt1_.UpdateMatrix();
	capsuleObj1_->SetDirectionalLight(capsuleLight_);
	capsuleObj1_->SetColor(capsuleColor1_);

	// 2
	capsuleWt2_.UpdateMatrix();
	capsuleObj2_->SetDirectionalLight(capsuleLight_);
	capsuleObj2_->SetColor(capsuleColor2_);

	/*timer++;
	if (timer >= 2) {
		timer = 0;
		capsuleWt2_.translate.x = ParlinNoise::Noise(rand) * 1.5f;
	}*/

#ifdef USE_IMGUI

	ImGui::Begin("DemoCollisionScene");
	ImGui::End();

	if (ImGui::TreeNode("Camera")) {
		ImGui::DragFloat3("Rotate", &viewProjection_.rotate.x, 0.005f);
		ImGui::DragFloat3("Translate", &viewProjection_.translate.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Capsule1")) {
		ImGui::Text("WorldTransform1");
		ImGui::DragFloat3("Scale1", &capsuleWt1_.scale.x, 0.01f, 0.0f, 10.0f);
		ImGui::DragFloat3("Rotate1", &capsuleWt1_.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate1", &capsuleWt1_.translate.x, 0.01f);
		ImGui::Text("ModelColor1");
		ImGui::ColorEdit4("ModelColor1", &capsuleColor1_.x);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Capsule2")) {
		ImGui::Text("WorldTransform2");
		ImGui::DragFloat3("Scale2", &capsuleWt2_.scale.x, 0.01f, 0.0f, 10.0f);
		ImGui::DragFloat3("Rotate2", &capsuleWt2_.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate2", &capsuleWt2_.translate.x, 0.01f);
		ImGui::Text("ModelColor2");
		ImGui::ColorEdit4("ModelColor2", &capsuleColor2_.x);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Light")) {
		ImGui::ColorEdit4("LightColor", &capsuleLight_.color.x);
		ImGui::DragFloat3("LightDirection", &capsuleLight_.direction.x, 0.1f);
		ImGui::TreePop();
	}

#endif // USE_IMGUI
}



/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void DemoCollisionScene::BackSpriteDraw() {

}



/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void DemoCollisionScene::ModelDraw() {

	// カプセルの描画処理
	capsuleObj1_->Draw(capsuleWt1_, viewProjection_);
	capsuleObj2_->Draw(capsuleWt2_, viewProjection_);
}



/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DemoCollisionScene::FrontSpriteDraw() {

}


