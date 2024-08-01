#include "DebugScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
DebugScene::DebugScene() {}


/// <summary>
/// デストラクタ
/// </summary>
DebugScene::~DebugScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void DebugScene::Initialize()
{
	uint32_t dds = TextureManager::LoadTexture("Texture", "airport_4k.dds");
	dds;
	/* ----- Camera カメラ ----- */
	camera_.Init({ 0.2f, 0.0f, 0.0f }, { 0.0f, 5.0f, -15.0f });
	cameraManager_ = CameraManager::GetInstance();
	cameraManager_->ReSetData(camera_);
	
	/* ----- Skydome 天球 ----- */
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();

	/* ----- Ground 床 ----- */
	ground_ = std::make_unique<Ground>();
	ground_->Init();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_ = make_unique<TestPostEffect>();
	testPostEffect_->Initialize();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_ = make_unique<TestHuman>();
	testHuman_->Init();
}



/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update(GameManager* state)
{
	state;

	/* ----- Camera カメラ ----- */
	camera_.Update();

	/* ----- Skydome 天球 ----- */
	skydome_->Update();

	/* ----- Ground 床 ----- */
	ground_->Update();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_->Update();

#ifdef _DEBUG

	ImGui::Begin("DebugScene");
	
	if (ImGui::Button("texLoad")) {

		TextureManager::LoadTexture("Texture","NormalMapTest.png");

	}
	camera_.DrawImGui();
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void DebugScene::BackSpriteDraw()
{

}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void DebugScene::ModelDraw()
{
	/* ----- Skydome 天球 ----- */
	//skydome_->draw3D();

	/* ----- Ground 床 ----- */
	//ground_->Draw3D();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_->Draw();

}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw()
{
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Draw();
}