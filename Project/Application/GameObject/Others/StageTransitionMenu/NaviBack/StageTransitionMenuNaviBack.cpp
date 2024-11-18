#include "StageTransitionMenuNaviBack.h"



/// <summary>
/// 初期化処理
/// </summary>
void StageTransitionMenuNaviBack::Init()
{
	// テクスチャ
	uint32_t backTexHD = TextureManager::LoadTexture(
		"Texture/Game/StageTransitionMenu", "StageTransitionMenu_BackScreen.png");
	uint32_t frameTexHD = TextureManager::LoadTexture(
		"Texture/Game/StageTransitionMenu",	"StageTransitionMenu_Frame.png");
	texHDArr_ = { backTexHD, frameTexHD };

	// スプライトサイズ
	Vector2 spriteSize = { 108.0f, 52.0f };
	sizeArr_ = { spriteSize, spriteSize };

	for (int i = 0; i < arraySize_; ++i) {

		// スプライト
		spriteArr_[i] = std::make_unique<Sprite>();
		spriteArr_[i]->Init(spriteSize);
		spriteArr_[i]->SetAnchor(SpriteAnchor::Center);
		spriteArr_[i]->SetTexture(texHDArr_[i]);
		spriteArr_[i]->SetColor(Samp::Color::BLACK);

		// トランスフォーム
		transArr_[i].Init();
	}
}


/// <summary>
/// 更新処理
/// </summary>
void StageTransitionMenuNaviBack::Update()
{
}


/// <summary>
/// 描画処理
/// </summary>
void StageTransitionMenuNaviBack::Draw2DFront()
{
	for (int i = 0; i < arraySize_; ++i) {
		spriteArr_[i]->SetColor(color_);
		spriteArr_[i]->Draw(transArr_[i]);
	}
}


/// <summary>
/// ImGuiの描画
/// </summary>
void StageTransitionMenuNaviBack::DrawImGui()
{
	if (ImGui::TreeNode("StageTransitionMenu_NaviBack")) {


		ImGui::TreePop();
	}
}
