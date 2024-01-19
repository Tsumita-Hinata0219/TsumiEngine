#include "DebugScene.h"



/// <summary>
/// デストラクタ
/// </summary>
DebugScene::~DebugScene() {}



/// <summary>
/// 初期化処理
/// </summary>
void DebugScene::Initialize() {

	viewProjection_.Initialize();
	viewProjection_.translate = { 0.0f, 0.0f, -15.0f };

	engineManual_ = std::make_unique<EngineManual>();
	engineManual_->Initialize();
}



/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update(GameManager* state) {

	engineManual_->Update();

	viewProjection_.UpdateMatrix();


#ifdef _DEBUG

	ImGui::Begin("DebugScene");
	ImGui::End();

	ImGui::Begin("Camera");
	ImGui::DragFloat3("Rotate", &viewProjection_.rotate.x, 0.005f);
	ImGui::DragFloat3("Translate", &viewProjection_.translate.x, 1.0f);
	ImGui::End();

#endif // _DEBUG
}



/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void DebugScene::BackSpriteDraw() {

	engineManual_->BackSpriteDraw(viewProjection_);
}



/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void DebugScene::ModelDraw() {

	engineManual_->ModelDraw(viewProjection_);
}



/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw() {

	engineManual_->FrontSpriteDraw(viewProjection_);
}


