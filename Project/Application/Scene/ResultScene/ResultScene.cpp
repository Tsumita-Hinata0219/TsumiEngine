#include "ResultScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene() {}


/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void ResultScene::Initialize()
{
	/* ----- Input インプット ----- */
	input_ = TsumiEngine::Input::GetInstance();

	/* ----- Camera カメラ ----- */
	cameraManager_ = CameraManager::GetInstance();
	camera_.Init();
	cameraManager_->ReSetData(camera_);

	/* ----- Result リザルト ----- */
	resultTexHD_ = TextureManager::LoadTexture("Texture/Result", "ResultSceneBG.png");
	resultSp_ = std::make_unique<Sprite>();
	resultSp_->Init({ 1280.0f, 720.0f });
	resultWt_.Initialize();

	/* ----- SceneTransition シーントランジション ----- */
	sceneTransition_ = SceneTransition::GetInstance();
	sceneTransition_->Init();
	sceneTransition_->StartFadeIn();
}


/// <summary>
/// 更新処理
/// </summary>
void ResultScene::Update(GameManager* state)
{
	state;

	/* ----- Camera カメラ ----- */
	camera_.Update();

	/* ----- Result リザルト ----- */
	resultWt_.UpdateMatrix();

	/* ----- SceneTransition シーントランジション ----- */
	sceneTransition_->Update();

	// ボタン押下でトランジション開始
	if (input_->Trigger(PadData::A)) {
		sceneTransition_->StartFadeOut();
	}
	// 画面が閉じたらシーン変更
	if (sceneTransition_->GetNowState() == TransitionState::Cloased) {
		state->ChangeSceneState(new TitleScene);
		return;
	}


#ifdef _DEBUG

	ImGui::Begin("ResultScene");

	ImGui::Text("");
	ImGui::Text("");

	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void ResultScene::BackSpriteDraw()
{
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void ResultScene::ModelDraw()
{
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void ResultScene::FrontSpriteDraw()
{
	/* ----- Result リザルト ----- */
	resultSp_->Draw(resultTexHD_, resultWt_);

	/* ----- SceneTransition シーントランジション ----- */
	sceneTransition_->Draw2DFront();
}
