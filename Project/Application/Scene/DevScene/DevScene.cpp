#include "DevScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
DevScene::DevScene()
{
	cameraManager_ = CameraManager::GetInstance();

	floor_ = std::make_unique<Floor>();
}


/// <summary>
/// デストラクタ
/// </summary>
DevScene::~DevScene()
{
}


/// <summary>
/// 初期化処理
/// </summary>
void DevScene::Initialize()
{
	cameraManager_->ReSet();
	cameraData_ = cameraManager_->GetCameraDataWeak();
	cameraData_.lock()->Init({ 0.15f, -0.3f, 0.0f }, { 7.0f, 4.0f, -20.0f });

	floor_->Init();
	floor_->SetScale(Vector3{ 20.0f, 1.0f, 20.0f });
	floor_->SetTranslate(Vector3{ 0.0f, -2.0f, 0.0f });
}


/// <summary>
/// 更新処理
/// </summary>
void DevScene::Update()
{
	cameraData_.lock()->Update();

	floor_->Update();
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void DevScene::BackSpriteDraw()
{
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void DevScene::ModelDraw()
{
	floor_->Draw3D();
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DevScene::FrontSpriteDraw()
{
}
