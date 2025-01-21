#include "GameManager.h"


// グローバル変数の定義
float g_ElapsedTime = 0.0f;

/// <summary>
/// コンストラクタ
/// </summary>
GameManager::GameManager(std::unique_ptr<IScene> initScene) {

	Tsumi::Initialize();
	scene_ = std::move(initScene);
	scene_->SetManager(this);
	scene_->Initialize();
	startTime_ = std::chrono::steady_clock::now();  // 開始時間を記録
	copyImage_ = std::make_unique<AbsentEffect>();
	copyImage_->Init();
}


/// <summary>
/// デストラクタ
/// </summary>
GameManager::~GameManager() {
	Tsumi::Finalize();
}


/// <summary>
/// ゲームループ
/// </summary>
void GameManager::Run() {

	TextLog::Init();
	TextLog::Load("Run_Start");
	while (Tsumi::ProcessMessage() == 0) {

		auto currentTime = std::chrono::steady_clock::now();
		g_ElapsedTime = std::chrono::duration<float>(currentTime - startTime_).count();

		Tsumi::BeginFlame();
		scene_->Update();

		//// ポストエフェクト
		DirectXManager::PreDrawForPostEffect();
		
		scene_->BackSpriteDraw();
		scene_->ModelDraw();

		DirectXManager::PostDrawForPostEffect();

		// スワップチェーン
		DirectXManager::PreDrawForSwapChain();

		copyImage_->Draw();
		scene_->FrontSpriteDraw();

		Tsumi::EndFlame();
		DirectXManager::PostDrawForSwapChain();
	}
	TextLog::Load("Run_End");
	TextLog::Close();

}


/// <summary>
/// シーンチェンジ
/// </summary>
void GameManager::ChangeSceneState(std::unique_ptr<IScene> newScene) {
	scene_.reset();
	scene_ = std::move(newScene);
	scene_->SetManager(this);
	scene_->Initialize();
	return;
}