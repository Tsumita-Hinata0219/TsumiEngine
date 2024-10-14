#include "SceneTransition.h"



// 初期化処理
void SceneTransition::Init()
{
	// テクスチャの読み込み
	textureHandle_ = TextureManager::LoadTexture("Texture", "Fade.png");

	// スプライトの初期化
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initn({ 1280.0f, 720.0f });
	// Textureの設定
	sprite_->SetTexture(textureHandle_);
	// Colorは黒
	sprite_->SetColor(Samp::Color::BLACK);

	// トランスフォームの初期化
	trans_.Init();

	// Dissolve関連の初期化
	dissolve_.isActive = true;
	dissolve_.maskTexHandle = TextureManager::LoadTexture("Texture", "noise0.png");

	// TransitionTimerの初期設定
	transitionDuration_ = 2.0f * 60.0f; // 2秒
	transitionTimer_.Init(0.0f, 2.0f * transitionDuration_);
}


// 更新処理
void SceneTransition::Update()
{
	// DissolveDataの設定
	sprite_->SetDissolveData(dissolve_);

	// 遷移処理
	FuncTransition();

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


// フェードイン開始
void SceneTransition::StartFadeIn()
{
	if (nowState_ == TransitionState::Cloased) {

		// ステート変更
		nowState_ = TransitionState::Opening;

		// 閾値の開始と目標を設定
		startThreshold_ = 0.0f;
		targetThreshold_ = 1.0f;

		// タイマースタート
		transitionTimer_.Start();
	}
}


// フェードアウト開始
void SceneTransition::StartFadeOut()
{
	if (nowState_ == TransitionState::Opened) {

		// ステート変更
		nowState_ = TransitionState::Closing;

		// 閾値の開始と目標を設定
		startThreshold_ = 1.0f;
		targetThreshold_ = 0.0f;

		// タイマースタート
		transitionTimer_.Start();
	}
}


// 遷移処理
void SceneTransition::FuncTransition()
{
	if (nowState_ == Opening || nowState_ == Closing) {

		transitionTimer_.Update(); // タイマー更新

		// 補間で閾値を変更
		dissolve_.threshold =
			startThreshold_ + (targetThreshold_ - startThreshold_) * 
			Ease::InSine(transitionTimer_.GetRatio());

		// タイマー終了
		if (transitionTimer_.IsFinish()) {

			// ステート変更
			if (nowState_ == Opening) {
				nowState_ = Opened;
			}
			else if (nowState_ == Closing) {
				nowState_ = Cloased;
			}

			// タイマー停止 & 時間の再設定
			transitionTimer_.Clear();
			transitionTimer_.Init(0.0f, 2.0f * transitionDuration_);
		}
	}
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
