#include "SceneTransition.h"



// 初期化処理
void SceneTransition::Init()
{
	// テクスチャの読み込み
	textureHandle_ = TextureManager::LoadTexture("Texture", "uvChecker.png");

	// スプライトの初期化
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initn({ 256.0f, 256.0f });

	// トランスフォームの初期化
	trans_.Init();

}


// 更新処理
void SceneTransition::Update()
{



}


// 描画処理
void SceneTransition::Draw2DFront()
{
	sprite_->Draw(textureHandle_, trans_);
}


// ImGuiの描画
void SceneTransition::DrawImGui()
{
	if (ImGui::TreeNode("SceneTransition")) {




		ImGui::TreePop();
	}


}
