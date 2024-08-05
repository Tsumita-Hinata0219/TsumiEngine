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

	/* ----- Title タイトル ----- */
	titleTexHD_ = TextureManager::LoadTexture("Texture/Title", "TitleSceneBG.png");
	titleSp_ = std::make_unique<Sprite>();
	titleSp_->Initialize({ 1280.0f, 720.0f });
	titleWt_.Initialize();

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

	/* ----- Camera カメラ ----- */
	camera_.Update();

	/* ----- Title タイトル ----- */
	titleWt_.UpdateMatrix();

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
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void TitleScene::ModelDraw()
{
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void TitleScene::FrontSpriteDraw()
{
	/* ----- Title タイトル ----- */
	titleSp_->Draw(titleTexHD_, titleWt_);

	/* ----- FadeManager フェードマネージャー ----- */
	fadeManager_->Draw();
}
