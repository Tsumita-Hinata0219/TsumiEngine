#include "TitleScene.h"



// 初期化処理
void TitleScene::Initialize()
{
	// メインカメラ
	GameCamera_.Initialize();

	// フェードの処理
	FadeManager::Initialize(func_FadeIn);

	funcFade_ = false;
}


// 更新処理
void TitleScene::Update(GameManager* state)
{
	/* ----- GameCamera ゲームカメラ----- */
	GameCamera_.UpdateMatrix();

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

}


// 前景スプライトの描画処理
void TitleScene::FrontSpriteDraw()
{
	FadeManager::Draw(GameCamera_);
}
