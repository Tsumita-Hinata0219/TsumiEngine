#include "DebugScene.h"
#include "Lua/Manager/LuaManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
DebugScene::DebugScene() 
{
	cameraManager_ = CameraManager::GetInstance();
	luaManager_ = LuaManager::GetInstance();
	dummyParticle_ = std::make_unique<DummyParticle>();
	floor_ = std::make_unique<Floor>();
}


/// <summary>
/// デストラクタ
/// </summary>
DebugScene::~DebugScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void DebugScene::Initialize()
{
	cameraManager_->ReSet();
	cameraData_ = cameraManager_->GetCameraDataWeak();
	cameraData_.lock()->Init({0.15f, -0.3f, 0.0f}, {7.0f, 4.0f, -20.0f});

	floor_->Init();
	floor_->SetScale(Vector3{ 20.0f, 1.0f, 20.0f });
	floor_->SetTranslate(Vector3{ 0.0f, -2.0f, 0.0f });

	dummyParticle_->Init();
}


/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update()
{
	cameraData_.lock()->Update();

	floor_->Update();

	dummyParticle_->Update();


#ifdef _DEBUG
	luaManager_->MonitorScript();
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
	floor_->Draw3D();
	dummyParticle_->Draw();
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw()
{
	
}