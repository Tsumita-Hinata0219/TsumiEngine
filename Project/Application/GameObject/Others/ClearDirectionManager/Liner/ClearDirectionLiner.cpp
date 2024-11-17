#include "ClearDirectionLiner.h"



/// <summary>
/// 初期化処理
/// </summary>
void ClearDirectionLiner::Init()
{
	// テクスチャ
	textureHandle_ = TextureManager::LoadTexture("Texture/Game/ClearDirection", "ClearDirectionLiner.png");

	// スプライト
	Vector2 screenSize = { 1280.0f, 720.0f };
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initn(screenSize);
	sprite_->SetTexture(textureHandle_);

	// トランスフォーム
	trans_.Init();

	// カラー
	color_ = Samp::Color::WHITE;
	color_.w = initAlpha_;

	// タイマー(10秒)
	timer_.Init(0.0f, 10.0f * 60.0f);
}


/// <summary>
/// 更新処理
/// </summary>
void ClearDirectionLiner::Update()
{
	// ステートが処理中
	if (state_ == ClearDirectionState::Processing) {
		timer_.Update(); // タイマー更新
		DirectionUpdate(); // 演出更新
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
void ClearDirectionLiner::Draw2DFront()
{
	sprite_->SetColor(color_);
	sprite_->Draw(trans_);
}


/// <summary>
/// 演出開始
/// </summary>
void ClearDirectionLiner::DirectionStart()
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
void ClearDirectionLiner::DirectionUpdate()
{
	// 初期値から目標値へアルファ値を補間する
	CalculateAlpha();
}


/// <summary>
/// 演出終了
/// </summary>
void ClearDirectionLiner::DirectionExsit()
{
	// ステートを終了へ
	state_ = ClearDirectionState::Finished;
}


/// <summary>
/// 初期値から目標値へアルファ値を補間する
/// </summary>
void ClearDirectionLiner::CalculateAlpha()
{
	// カラーのAlpha値を補間で上げる
	color_.w =
		initAlpha_ + (targetAlpha_ - initAlpha_) *
		Ease::OutExpo(timer_.GetRatio());
}


/// <summary>
/// ImGuiの描画
/// </summary>
void ClearDirectionLiner::DrawImGui()
{
	if (ImGui::TreeNode("ClearDirection_Liner")) {

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

