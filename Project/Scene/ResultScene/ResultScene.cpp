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
	input_ = Input::GetInstance();

	/* ----- Camera カメラ ----- */
	cameraManager_ = CameraManager::GetInstance();
	camera_.Init();
	cameraManager_->ReSetData(camera_);

	/* ----- Result リザルト ----- */
	resultTexHD_ = TextureManager::LoadTexture("Texture/Result", "ResultSceneBG.png");
	resultSp_ = std::make_unique<Sprite>();
	resultSp_->Initialize({ 1280.0f, 720.0f });
	resultWt_.Initialize();

	/* ----- FadeManager フェードマネージャー ----- */
	fadeManager_ = FadeManager::GetInstance();
	fadeManager_->Initialize(func_FadeIn);
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

	// ボタン押下でフェードイン
	if (input_->Trigger(PadData::A)) {
		isFadeFunc_ = true;
	}

	// フェード処理のフラグが立っていたらフェード処理に入る
	if (isFadeFunc_) {

		if (fadeManager_->IsFadeIn()) {
			state->ChangeSceneState(new TitleScene);
			return;
		}
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

	/* ----- FadeManager フェードマネージャー ----- */
	fadeManager_->Draw();
}
