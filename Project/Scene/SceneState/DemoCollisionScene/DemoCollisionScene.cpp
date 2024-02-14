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
	capsuleObj_ = make_unique<Model>();
	capsuleObj_->CreateFromObj("Capsule");
	capsuleObj_->SetModelDrawType(Phong);
	capsuleWt_.Initialize();
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


	// カプセルの更新処理
	capsuleWt_.UpdateMatrix();
	capsuleObj_->SetDirectionalLight(capsuleLight_);
	capsuleObj_->SetColor(capsuleColor_);


#ifdef USE_IMGUI

	ImGui::Begin("DemoCollisionScene");
	ImGui::End();

	if (ImGui::TreeNode("Camera")) {
		ImGui::DragFloat3("Rotate", &viewProjection_.rotate.x, 0.005f);
		ImGui::DragFloat3("Translate", &viewProjection_.translate.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Capsule")) {
		ImGui::Text("WorldTransform");
		ImGui::DragFloat3("Scale", &capsuleWt_.scale.x, 0.01f, 0.0f, 10.0f);
		ImGui::DragFloat3("Rotate", &capsuleWt_.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &capsuleWt_.translate.x, 0.01f);
		ImGui::Text("ModelColor");
		ImGui::ColorEdit4("ModelColor", &capsuleColor_.x);
		ImGui::Text("Light");
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
	capsuleObj_->Draw(capsuleWt_, viewProjection_);
}



/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DemoCollisionScene::FrontSpriteDraw() {

}


