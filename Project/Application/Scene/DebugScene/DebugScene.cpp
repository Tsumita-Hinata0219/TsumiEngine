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
	/* ----- ConfigManager コンフィグマネージャー ----- */
	configManager_ = ConfigManager::GetInstance();
	configManager_->LoadFile();

	/* ----- Camera カメラ ----- */
	camera_.Init({ 0.2f, 0.0f, 0.0f }, { 0.0f, 1.7f, -4.0f });
	cameraManager_ = CameraManager::GetInstance();
	cameraManager_->ReSetData(camera_);
	
	/* ----- Skydome 天球 ----- */
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();

	/* ----- Skybox 天箱 ----- */
	skybox_ = std::make_unique<Skybox>();
	uint32_t dds = TextureManager::LoadTexture("Texture", "DemoSkybox.dds");
	skybox_->Init(dds);

	/* ----- Ground 床 ----- */
	ground_ = std::make_unique<Ground>();
	ground_->Init();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_ = make_unique<TestPostEffect>();
	testPostEffect_->Init();

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

	/* ----- Skybox 天箱 ----- */
	skybox_->Update();

	/* ----- Ground 床 ----- */
	ground_->Update();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_->Update();

#ifdef _DEBUG

	ImGui::Begin("DebugScene");
	camera_.DrawImGui();
	ImGui::End();

	/* ----- ConfigManager コンフィグマネージャー ----- */
	configManager_->DrawImGui();

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
	//skydome_->Draw3D();

	/* ----- Skybox 天箱 ----- */
	skybox_->Draw();

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