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
	cameraManager_ = CameraManager::GetInstance();
	cameraManager_->ReSet();
	cameraData_ = cameraManager_->GetCameraDataWeak();
	cameraData_.lock()->Init({0.15f, -0.3f, 0.0f}, {7.0f, 4.0f, -20.0f});
	
	skybox_ = std::make_unique<Skybox>();
	uint32_t dds = TextureManager::LoadTexture("Texture", "DemoSkybox.dds");
	skybox_->Init(dds);

	dummyParticle_ = std::make_unique<DummyParticle>();
	dummyParticle_->Init();

	floor_ = std::make_unique<Floor>();
	floor_->Init();
	floor_->SetScale(Vector3{ 20.0f, 1.0f, 20.0f });
	floor_->SetTranslate(Vector3{ 0.0f, -2.0f, 0.0f });

	luaManager_ = LuaManager::GetInstance();
	luaManager_->LoadScript("LuaScript", "Test.lua");

	luaScript_ = luaManager_->GetScript("Test");

	int test1 = luaScript_.lock()->GetVariable<int>("intValue");
	test1;
	float test2 = luaScript_.lock()->GetVariable<float>("floatValue");
	test2;
}


/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update()
{
	cameraData_.lock()->Update();
	dummyParticle_->Update();
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
	dummyParticle_->Draw();
	floor_->Draw3D();
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw()
{
	
}