#include "StageTransitionMenuMoji.h"



/// <summary>
/// 初期化処理
/// </summary>
void StageTransitionMenuMoji::Init(const std::string& fileName)
{
	// テクスチャ
	textureHandle_ = TextureManager::LoadTexture("Texture/Game/StageTransitionMenu", fileName);

	// スプライト
	Vector2 screenSize = { 1280.0f, 720.0f };
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initn(screenSize);
	sprite_->SetAnchor(SpriteAnchor::Center);
	sprite_->SetTexture(textureHandle_);

	// トランスフォーム
	trans_.Init();

	// カラー
	color_ = color_ = Samp::Color::WHITE;
}


/// <summary>
/// 更新処理
/// </summary>
void StageTransitionMenuMoji::Update()
{


#ifdef _DEBUG
	// ImGuiの描画
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void StageTransitionMenuMoji::Draw2DFront()
{
	sprite_->SetColor(color_);
	sprite_->Draw(trans_);
}


/// <summary>
/// ImGuiの描画
/// </summary>
void StageTransitionMenuMoji::DrawImGui()
{
	if (ImGui::TreeNode("StageTransitionMenu_Moji")) {



		ImGui::TreePop();
	}
}

