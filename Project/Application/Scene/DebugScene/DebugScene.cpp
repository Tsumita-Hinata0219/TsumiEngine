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
	/* ----- Camera カメラ ----- */
	cameraManager_ = CameraManager::GetInstance();
	cameraManager_->ReSet();
	cameraData_ = cameraManager_->GetCameraDataWeak();
	cameraData_.lock()->Init({0.15f, 0.0f, 0.0f}, {0.0f, 4.0f, -23.0f});
	
	/* ----- Skybox 天箱 ----- */
	skybox_ = std::make_unique<Skybox>();
	uint32_t dds = TextureManager::LoadTexture("Texture", "DemoSkybox.dds");
	skybox_->Init(dds);

	/* ----- DemoParticle デモパーティクル ----- */
	demoParticle_ = std::make_unique<DemoParticle>();
	demoParticle_->Init();

	/* ----- Floor 床 ----- */
	floor_ = std::make_unique<Floor>();
	floor_->Init();
	floor_->SetScale(Vector3{ 20.0f, 1.0f, 20.0f });
	floor_->SetTranslate(Vector3{ 0.0f, -2.0f, 0.0f });
}


/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update()
{
	/* ----- Camera カメラ ----- */
	cameraData_.lock()->Update();

	/* ----- DemoParticle デモパーティクル ----- */
	demoParticle_->Update();

	/* ----- Floor 床 ----- */
	floor_->Update();

#ifdef _DEBUG
	ImGui::Begin("DebugScene");
	cameraData_.lock()->DrawImGui();
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
	/* ----- Floor 床 ----- */
	floor_->Draw3D();

	/* ----- DemoParticle デモパーティクル ----- */
	demoParticle_->Draw();
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw()
{
	
}