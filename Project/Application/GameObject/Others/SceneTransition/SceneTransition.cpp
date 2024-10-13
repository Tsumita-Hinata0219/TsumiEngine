#include "SceneTransition.h"



// 初期化処理
void SceneTransition::Init()
{
	// テクスチャの読み込み
	textureHandle_ = TextureManager::LoadTexture("Texture", "uvChecker.png");

	// スプライトの初期化
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initn({ 1280.0f, 720.0f });
	// Textureの設定
	sprite_->SetTexture(textureHandle_);

	// トランスフォームの初期化
	trans_.Init();

	// Dissolve関連の初期化
	dissolve_.isActive = false;
	dissolve_.threshold = 1.0f;
	dissolve_.maskTexHandle = TextureManager::LoadTexture("Texture", "SceneTransitionMaskTexture.png");

}


// 更新処理
void SceneTransition::Update()
{
	// DissolveDataの設定
	sprite_->SetDissolveData(dissolve_);

#ifdef _DEBUG
	// ImGuiの描画
	DrawImGui();
#endif // _DEBUG
}


// 描画処理
void SceneTransition::Draw2DFront()
{
	sprite_->Draw(trans_);
}


// ImGuiの描画
void SceneTransition::DrawImGui()
{
	if (ImGui::TreeNode("SceneTransition")) {

		ImGui::Text("Dissolve");
		ImGui::RadioButton("Disabled", &dissolve_.isActive, 0); ImGui::SameLine();
		ImGui::RadioButton("Enabled", &dissolve_.isActive, 1);
		ImGui::DragFloat("threshold", &dissolve_.threshold, 0.01f, 0.0f, 1.0f);
		ImGui::TreePop();
	}
}
