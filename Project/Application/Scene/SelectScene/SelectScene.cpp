#include "SelectScene.h"



/// <summary>
/// 初期化処理
/// </summary>
void SelectScene::Initialize()
{
	// カメラ
	cameraManager_ = CameraManager::GetInstance();
	camera_.Init();
	cameraManager_->ReSetData(camera_);

	// セレクト
	selectManager_ = StageSelectManager::GetInstrance();
	selectManager_->Init();

	// シーントランジション
	sceneTransition_ = SceneTransition::GetInstance();
	sceneTransition_->Init();
	sceneTransition_->SetState(Cloased);
	sceneTransition_->StartFadeIn();
}


/// <summary>
/// 更新処理
/// </summary>
void SelectScene::Update(GameManager* state)
{
	// カメラ
	camera_.Update();

	// シーントランジション
	sceneTransition_->Update();
	// シーントランジション中は以下の処理に入らない
	if (sceneTransition_->GetNowState() == TransitionState::Opening ||
		sceneTransition_->GetNowState() == TransitionState::Closing) {
		return;
	}

	// セレクト
	selectManager_->Update();

	// 決定ボタンが押されたらシーンチェンジ
	if (selectManager_->IsSelect()) {
		sceneTransition_->StartFadeOut();
	}
	// 画面が閉じたらシーン変更
	if (sceneTransition_->GetNowState() == TransitionState::Cloased) {
		state->ChangeSceneState(new GameScene);
		return;
	}

#ifdef _DEBUG
	ImGui::Begin("ResultScene");
	ImGui::End();
#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void SelectScene::BackSpriteDraw()
{
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void SelectScene::ModelDraw()
{
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void SelectScene::FrontSpriteDraw()
{
	// シーントランジション
	sceneTransition_->Draw2DFront();
}
