#include "ClearDirectionBackScreen.h"



/// <summary>
/// 初期化処理
/// </summary>
void ClearDirectionBackScreen::Init()
{
	// テクスチャ
	textureHandle_ = TextureManager::LoadTexture("Texture/Game/ClearDirection", "ClearDirectionBackScreen.png");

	// スプライト
	Vector2 screenSize = { 1280.0f, 720.0f };
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initn(screenSize);
	sprite_->SetTexture(textureHandle_);

	// トランスフォーム
	trans_.Init();

	// カラー
	color_ = Samp::Color::BLACK;
	color_.w = 0.0f;

	// タイマー
	timer_.Init(0.0f, 1.0f * 30.0f);
}


/// <summary>
/// 更新処理
/// </summary>
void ClearDirectionBackScreen::Update()
{
	// ステートが処理中ならタイマー更新
	if (state_ == ClearDirectionState::Processing) {
		timer_.Update();
	}

	// タイマーが終了したら終了時処理
	if (timer_.IsFinish()) {
		DirectionExsit();
	}

#ifdef _DEBUG
	// ImGuiの描画
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void ClearDirectionBackScreen::Draw2DFront()
{
	sprite_->SetColor(color_);
	sprite_->Draw(trans_);
}


/// <summary>
/// 演出開始
/// </summary>
void ClearDirectionBackScreen::DirectionStart()
{
	if (state_ == ClearDirectionState::Idle) {

		// ステートを処理中へ
		state_ = ClearDirectionState::Processing;
		// タイマースタート
		timer_.Start();
	}
}


/// <summary>
/// 演出更新
/// </summary>
void ClearDirectionBackScreen::DirectionUpdate()
{
}


/// <summary>
/// 演出終了
/// </summary>
void ClearDirectionBackScreen::DirectionExsit()
{
	// ステートを終了へ
	state_ = ClearDirectionState::Finished;
}


/// <summary>
/// ImGuiの描画
/// </summary>
void ClearDirectionBackScreen::DrawImGui()
{
	if (ImGui::TreeNode("ClearDirection_Screen")) {

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

