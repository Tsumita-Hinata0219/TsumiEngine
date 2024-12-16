#include "TitleScene.h"
#include "../../GameManager/GameManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene() {}


/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	/* ----- Input インプット ----- */
	input_ = Input::GetInstance();

	/* ----- Camera カメラ ----- */
	cameraManager_ = CameraManager::GetInstance();
	camera_.Init();
	cameraManager_->ReSetData(camera_);

	/* ----- AbsentEffect アブセントエフェクト ----- */
	absentEffect_ = std::make_unique<AbsentEffect>();
	absentEffect_->Init();

	/* ----- RetroCRT レトロエフェクト ----- */
	retroCRT_ = std::make_unique<RetroCRTEffect>();
	retroCRT_->Init();
	retroEffectData_ = {
		Samp::Color::WHITE,
		0.15f, true,
		{0.003f, 0.005f}, {-0.003f, -0.005f}, true,
		0.15f, true,
		0.3f, true,
		0.0f, false,
		WinApp::WindowSize(),
		0.0f
	};
	retroCRT_->SetMtlData(retroEffectData_);

	/* ----- TitleBackGround タイトルバックグラウンド ----- */
	titleBG_ = std::make_unique<TitleBackGround>();
	titleBG_->Init();

	/* ----- TitleUIManager タイトルラベルUI ----- */
	uiManager_ = std::make_unique<TitleUIManager>();
	uiManager_->Init();

	/* ----- SceneTransition シーントランジション ----- */
	sceneTransition_ = SceneTransition::GetInstance();
	sceneTransition_->Init();
	sceneTransition_->SetState(Cloased);
	sceneTransition_->StartFadeIn();
}


/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{
	/* ----- Camera カメラ ----- */
	camera_.Update();

	/* ----- TitleBackGround タイトルバックグラウンド ----- */
	titleBG_->Update();
	
	/* ----- TitleUIManager タイトルラベルUI ----- */
	uiManager_->Update();

	/* ----- SceneTransition シーントランジション ----- */
	sceneTransition_->Update();

	// ボタン押下でトランジション開始
	if (input_->Trigger(PadData::A) || input_->Trigger(DIK_SPACE)) {
		sceneTransition_->StartFadeOut();
	}
	// 画面が閉じたらシーン変更
	if (sceneTransition_->GetNowState() == TransitionState::Cloased) {
		Manager_->ChangeSceneState(std::make_unique<SelectScene>());
		return;
	}


#ifdef _DEBUG
	ImGui::Begin("TitleScene");
	//retroEffectData_.DrawImGui();
	camera_.DrawImGui();
	ImGui::End();
#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void TitleScene::BackSpriteDraw()
{
	/* ----- TitleBackGround タイトルバックグラウンド ----- */
	titleBG_->Draw2DBack();
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void TitleScene::ModelDraw()
{
	/* ----- TitleUIManager タイトルラベルUI ----- */
	uiManager_->Draw3D();
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void TitleScene::FrontSpriteDraw()
{
	/* ----- AbsentEffect アブセントエフェクト----- */
	absentEffect_->Draw();

	/* ----- RetroCRT レトロエフェクト ----- */
	retroCRT_->SetMtlData(retroEffectData_);
	retroCRT_->Draw();

	/* ----- TitleUIManager タイトルラベルUI ----- */
	uiManager_->Draw2DFront();
	
	/* ----- TitleBackGround タイトルバックグラウンド ----- */
	titleBG_->Draw2DFront();

	/* ----- SceneTransition シーントランジション ----- */
	sceneTransition_->Draw2DFront();
}
