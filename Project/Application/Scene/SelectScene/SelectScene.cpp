#include "SelectScene.h"
#include "GameManager/GameManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void SelectScene::Initialize()
{
	// Camera カメラ
	cameraManager_ = CameraManager::GetInstance();
	cameraManager_->ReSet();
	cameraData_ = cameraManager_->GetCameraDataWeak();
	cameraData_.lock()->Init({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -30.0f });

	// セレクト
	selectManager_ = std::make_unique<StageSelectManager>();
	selectManager_->Init();

	// 一回だけ通る処理
	if (!isVisited_) {
		OnceInit();
	}

	texture_ = TextureManager::LoadTexture("Texture/Select", "selectnavi.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Init({ 1280.0f, 720.0f });
	sprite_->SetTexture(texture_);
	trans_.Init();

	// シーントランジション
	sceneTransition_ = SceneTransition::GetInstance();
	sceneTransition_->Init();
	sceneTransition_->SetState(Cloased);
	sceneTransition_->StartFadeIn();
}


/// <summary>
/// 更新処理
/// </summary>
void SelectScene::Update()
{
	// カメラ
	cameraData_.lock()->Update();

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

		// GameDataに選択したステージ番号を保存しておく
		GameData::GetInstance()->Set_StageSelectNum(selectManager_->GetSelectStageNum());
		// シーントランジション開始
		sceneTransition_->StartFadeOut();
	}
	// 画面が閉じたらシーン変更
	if (sceneTransition_->GetNowState() == TransitionState::Cloased) {
		Manager_->ChangeSceneState(std::make_unique<GameScene>());
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
	selectManager_->Draw2DFront();

	sprite_->Draw(trans_);

	// シーントランジション
	sceneTransition_->Draw2DFront();
}


/// <summary>
/// ゲーム起動してから一度だけ入る初期化
/// </summary>
void SelectScene::OnceInit()
{
	// ToDo : 以下のパスの変数は外部ファイルに追い出して実装する

	// ステージファイルパスの設定（ローカル変数）
	std::vector<std::string> stagePaths = {
		"Stage_Demo.json",
		"Stage_1.json",
		"Stage_2.json",
		"Stage_3.json",
		"Stage_4.json",
		"Stage_5.json"
	};

	// ToDo

	// 保存しておく
	for (auto& element : stagePaths) {
		GameData::GetInstance()->AddStageJsonFilePath(element);
	}

	// 一度訪れた￥フラグを立てておく
	isVisited_;
}
