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
	camera_.Init({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -5.0f });
	cameraManager_ = CameraManager::GetInstance();
	cameraManager_->ReSetData(camera_);
}



/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update() {}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void DebugScene::BackSpriteDraw() {}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void DebugScene::ModelDraw() {}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw() {}