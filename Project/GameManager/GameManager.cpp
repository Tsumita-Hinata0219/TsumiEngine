#include "GameManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameManager::GameManager() {

	Tsumi::Initialize();
	Scene_ = new GameScene();
	Scene_->Initialize();
	absentEffect_ = std::make_unique<AbsentEffect>();
	absentEffect_->Initialize();
}


/// <summary>
/// デストラクタ
/// </summary>
GameManager::~GameManager() {

	delete Scene_;
	Tsumi::Finalize();
}


/// <summary>
/// ゲームループ
/// </summary>
void GameManager::Run() {

	TextLog::Init();
	TextLog::Load("Run_Start");
	while (Tsumi::ProcessMessage() == 0) {

		Tsumi::BeginFlame();
		Scene_->Update(this);

		//// ポストエフェクト
		DirectXCommon::PreDrawForPostEffect();
		
		Scene_->BackSpriteDraw();
		Scene_->ModelDraw();

		DirectXCommon::PostDrawForPostEffect();

		// スワップチェーン
		DirectXCommon::PreDrawForSwapChain();

		absentEffect_->Draw(nullptr);
		Scene_->FrontSpriteDraw();

		Tsumi::EndFlame();
		DirectXCommon::PostDrawForSwapChain();
	}
	TextLog::Load("Run_End");
	TextLog::Close();
}


/// <summary>
/// シーンチェンジ
/// </summary>
void GameManager::ChangeSceneState(IScene* newScene) {

	delete Scene_;
	Scene_ = newScene;
	Scene_->Initialize();
	return;
}