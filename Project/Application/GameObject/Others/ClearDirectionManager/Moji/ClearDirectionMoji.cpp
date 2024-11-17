#include "ClearDirectionMoji.h"



/// <summary>
/// 初期化処理
/// </summary>
void ClearDirectionMoji::Init()
{
	// テクスチャ
	textureHandle_ = TextureManager::LoadTexture("Texture/Game/ClearDirection", "ClearDirectionMoji.png");

	// スプライト
	Vector2 screenSize = { 1280.0f, 720.0f };
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initn(screenSize);
	sprite_->SetTexture(textureHandle_);

	// トランスフォーム
	trans_.Init();

	// カラー
	color_ = Samp::Color::WHITE;
}


/// <summary>
/// 更新処理
/// </summary>
void ClearDirectionMoji::Update()
{


#ifdef _DEBUG
	// ImGuiの描画
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void ClearDirectionMoji::Draw2DFront()
{
	sprite_->SetColor(color_);
	sprite_->Draw(trans_);
}


/// <summary>
/// 演出開始
/// </summary>
void ClearDirectionMoji::StartDirection()
{
	if (state_ == ClearDirectionState::Idle) {
		
		// ステートを処理中へ
		state_ = ClearDirectionState::Processing;

	}
}


/// <summary>
/// ImGuiの描画
/// </summary>
void ClearDirectionMoji::DrawImGui()
{
	if (ImGui::TreeNode("ClearDirection_Moji")) {

		ImGui::Text("Transform");
		trans_.DrawImGui();
		ImGui::Text("");

		ImGui::ColorEdit4("Color", &color_.x);
		ImGui::Text("");

		if (state_ == ClearDirectionState::Idle) {
			ImGui::Text("State = Idle");
		}
		else if (state_ == ClearDirectionState::Processing) {
			ImGui::Text("State = Processing");
		}
		else if (state_ == ClearDirectionState::Finished) {
			ImGui::Text("State = Finished");
		}
		ImGui::Text("");

		ImGui::TreePop();
	}
}


