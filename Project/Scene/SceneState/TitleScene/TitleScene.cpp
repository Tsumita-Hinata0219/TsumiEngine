#include "TitleScene.h"



// 初期化処理
void TitleScene::Initialize()
{
	// メインカメラ
	GameCamera_.Initialize();

	// フェードの処理
	FadeManager::Initialize(func_FadeIn);

	funcFade_ = false;

	texHD_ = TextureManager::LoadTexture("Title.png");
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(Vector2::zero, WinApp::WindowSize());
	st_.Initialize();

	/* ----- Skydome スカイドーム ----- */
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();


	/* ----- Ground グラウンド ----- */
	ground_ = make_unique<Ground>();
	ground_->Initialize();
}


// 更新処理
void TitleScene::Update(GameManager* state)
{
	/* ----- GameCamera ゲームカメラ----- */
	GameCamera_.UpdateMatrix();
	GameCamera_.translate.z++;

	if (GameCamera_.translate.z >= 500.0f) {
		GameCamera_.translate.z = 0.0f;
	}


	if (KeysInput::TriggerKey(DIK_I)) {
		funcFade_ = true;
	}
	
	// ゲームパッドを見接続なら何もせず抜ける
	if (!GamePadInput::GetJoyStickState(joyState_)) {
		return;
	}
	if (GamePadInput::PressButton(joyState_, XINPUT_GAMEPAD_B)) {
		funcFade_ = true;
	}

	if (funcFade_) {
		if (FadeManager::IsFadeIn()) {

			state->ChangeSceneState(new GameScene());
			return;
		}
	}

	/* ----- Skydome スカイドーム ----- */
	skydome_->Update();


	/* ----- Ground グラウンド ----- */
	ground_->Update();

	st_.UpdateMatrix();

#ifdef _DEBUG

	ImGui::Begin("TitleScene");
	ImGui::Text("GameCamera");
	ImGui::DragFloat3("Rotate", &GameCamera_.rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &GameCamera_.translate.x, 0.01f);
	ImGui::End();

#endif // _DEBUG
}


// 背景スプライトの描画処理
void TitleScene::BackSpriteDraw()
{

}


// ３Dオブジェクトの描画処理
void TitleScene::ModelDraw()
{
	/* ----- Skydome スカイドーム ----- */
	skydome_->Draw(GameCamera_);

	/* ----- Ground グラウンド ----- */
	ground_->Draw(GameCamera_);
}


// 前景スプライトの描画処理
void TitleScene::FrontSpriteDraw()
{
	sprite_->Draw(texHD_, st_, GameCamera_);
	FadeManager::Draw(GameCamera_);
}
