#include "TitleScene.h"



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

	/* ----- TestPostffect テストポストエフェクト ----- */
	testPostEffect_ = std::make_unique<TestPostEffect>();
	testPostEffect_->Init();

	/* ----- Skybox 天箱 ----- */
	skybox_ = std::make_unique<Skybox>();
	uint32_t dds = TextureManager::LoadTexture("Texture", "kokuban.dds");
	skybox_->Init(dds);

	/* ----- TitleScreen タイトルスクリーン ----- */
	titleScreen_ = std::make_unique<TitleScreen>();
	titleScreen_->Init();

	/* ----- TitleBackGround タイトルバックグラウンド ----- */
	titleBG_ = std::make_unique<TitleBackGround>();
	titleBG_->Init();

	/* ----- TitleLabelUI タイトルラベルUI ----- */
	titleLabel_ = std::make_unique<TitleLabelUI>();
	titleLabel_->Init();

	/* ----- FadeManager フェードマネージャー ----- */
	fadeManager_ = FadeManager::GetInstance();
	fadeManager_->Initialize(func_FadeIn);
}


/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update(GameManager* state)
{
	state;

	/* ----- TestPostffect テストポストエフェクト ----- */
	testPostEffect_->Update();

	/* ----- Camera カメラ ----- */
	camera_.Update();

	/* ----- Skybox 天箱 ----- */
	skybox_->Update();

	/* ----- TitleScreen タイトルスクリーン ----- */
	titleScreen_->Update();

	/* ----- TitleBackGround タイトルバックグラウンド ----- */
	titleBG_->Update();
	
	/* ----- TitleLabelUI タイトルラベルUI ----- */
	titleLabel_->Update();

	// ボタン押下でフェードイン
	if (input_->Trigger(PadData::A)) {
		isFadeFunc_ = true;
	}

	// フェード処理のフラグが立っていたらフェード処理に入る
	if (isFadeFunc_) {

		if (fadeManager_->IsFadeIn()) {
			state->ChangeSceneState(new GameScene);
			return;
		}
	}

#ifdef _DEBUG

	ImGui::Begin("TitleScene");

	ImGui::Text("");
	ImGui::Text("");

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
	/* ----- Skybox 天箱 ----- */
	//skybox_->Draw();

	/* ----- TitleScreen タイトルスクリーン ----- */
	//titleScreen_->Draw3D();

	/* ----- TitleLabelUI タイトルラベルUI ----- */
	titleLabel_->Draw3D();
}\


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void TitleScene::FrontSpriteDraw()
{
	/* ----- AbsentEffect アブセントエフェクト----- */
	absentEffect_->Draw();

	/* ----- TestPostffect テストポストエフェクト ----- */
	testPostEffect_->Draw();

	/* ----- TitleScreen タイトルスクリーン ----- */
	//titleScreen_->Draw2DFront();

	/* ----- TitleLabelUI タイトルラベルUI ----- */
	titleLabel_->Draw2DFront();
	
	/* ----- TitleBackGround タイトルバックグラウンド ----- */
	titleBG_->Draw2DFront();

	/* ----- FadeManager フェードマネージャー ----- */
	fadeManager_->Draw();
}
