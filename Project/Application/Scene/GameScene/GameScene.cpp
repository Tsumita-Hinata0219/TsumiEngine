#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() 
{
	input_ = Input::GetInstance();
	CollisionManager_ = CollisionManager::GetInstance();
	absentEffect_ = std::make_unique<AbsentEffect>();
	testPostEffect_ = make_unique<TestPostEffect>();
	gameSceneUI_ = std::make_unique<GameSceneUI>();
	gameCamera_ = std::make_unique<GameCamera>();
	startDirection_ = std::make_unique<StartDirection>();
	skybox_ = std::make_unique<Skybox>();
	floor_ = std::make_unique<Floor>();
	player_ = make_unique<Player>();
	enemyManager_ = std::make_unique<EnemyManager>();
	sceneTransition_ = SceneTransition::GetInstance();
	STMenuManager_ = std::make_unique<StageTransitionMenuManager>();
}


/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() 
{

}


/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize()
{
	// ──────── クラスにポインタを渡す
	// プレイヤーにカメラを渡す
	player_->SetGameCamera(gameCamera_.get());
	// カメラにプレイヤーを渡す
	gameCamera_->SetPlayer(player_.get());
	// エネミーにプレイヤーを渡す
	enemyManager_->SetPlayer(player_.get());


	// ──────── JsonManager
	JsonManager* jsonManager = JsonManager::GetInstance();
	jsonManager->LoadSceneFile("Json", "Stage_Demo.json");

	// ──────── AbsentEffect
	absentEffect_->Init();

	// ──────── TestPostEffect
	testPostEffect_->Init();

	// ──────── GameSceneUI
	gameSceneUI_->Init();

	// ──────── GameCamera
	gameCamera_->SetCameraType(GameCameraType::TOPDOWN);
	gameCamera_->Init();

	// ──────── StartDirection
	startDirection_->Init();

	// ──────── Skybox
	uint32_t dds = TextureManager::LoadTexture("Texture", "dot.dds");
	skybox_->Init(dds);

	// ──────── Floor
	floor_->Init();
	floor_->LoadEntityData(jsonManager->GetEntityData("Floor"));

	// ──────── Player
	player_->Init();
	player_->LoadEntityData(jsonManager->GetEntityData("Player"));

	// ──────── EnemyManager
	enemyManager_->Init();
	enemyManager_->LoadEntityData(jsonManager->GetEntityData("BasicEnemy"));
	enemyManager_->LoadEntityData(jsonManager->GetEntityData("StaticEnemy"));

	// ──────── SceneTransition
	STMenuManager_->Init();

	// ──────── StageTransitionMenuManager
	sceneTransition_->Init();
	sceneTransition_->SetState(Cloased);
	sceneTransition_->StartFadeIn();
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state)
{
	state;
	// ──────── TestPostEffect
	testPostEffect_->Update();

	// ──────── GameSceneUI
	gameSceneUI_->Update();

	// ──────── GameCamera
	gameCamera_->Update();

	// ──────── Skybox
	skybox_->Update();
	
	// ──────── Floor
	floor_->Update();

	// ──────── StageTransitionMenuManager
	sceneTransition_->Update();
	// 画面が閉じたらシーン変更
	if (sceneTransition_->GetNowState() == TransitionState::Cloased) {

		// セレクトバーが何を選択したかでチェンジ先シーンを変える
		if (STMenuManager_->GetSelect() == MenuSelect::Back) {
			state->ChangeSceneState(new TitleScene);
		}
		else if (STMenuManager_->GetSelect() == MenuSelect::Next) {
			state->ChangeSceneState(new GameScene);
		}
		return;
	}
	// 終了処理
	STMenuManager_->FuncEndDirection();
	// シーントランジション中は以下の処理に入らない
	if (sceneTransition_->GetNowState() == TransitionState::Opening ||
		sceneTransition_->GetNowState() == TransitionState::Closing) {
		return;
	}

	// ──────── StartDirection
	startDirection_->Update();
	if (!startDirection_->IsFinish()) { return; }
	
	// ──────── StageTransitionMenuManager
	STMenuManager_->Update();
	SceneChangeCheck();
	if (STMenuManager_->GetState() == MenuDirectionState::Processing) {
		return;
	}
	if (input_->Trigger(DIK_RETURN)) {
		state->ChangeSceneState(new TitleScene());
		return;
	}

	// ──────── Player
	player_->Update();

	// ──────── EnemyManager
	enemyManager_->Update();

	// ──────── CollisionManager
	CollisionManager_->Update();


#ifdef _DEBUG
	ImGui::Begin("GameScene");
	ImGui::Text("");
	CollisionManager_->Update();
	ImGui::End();
#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void GameScene::BackSpriteDraw()
{
	// ──────── GameSceneUI
	gameSceneUI_->Draw2DBack();

	// ──────── Player
	player_->Draw2DBack();
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw()
{
	// ──────── Skybox
	skybox_->Draw();

	// ──────── Floor
	floor_->Draw3D();

	// ──────── Player
	player_->Draw3D();

	// ──────── EnemyManager
	enemyManager_->Draw3D();
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw()
{
	absentEffect_->Draw();

	// ──────── TestPostEffect
	testPostEffect_->Draw();

	if (STMenuManager_->GetState() != MenuDirectionState::Processing) {

		// ──────── GameSceneUI
		gameSceneUI_->Draw2DFront();

		// ──────── Player
		player_->Draw2DFront();
	}

	// ──────── StartDirection
	startDirection_->Draw2DFront();

	// ──────── StageTransitionMenuManager
	STMenuManager_->Draw2DFront();

	// ──────── SceneTransition
	sceneTransition_->Draw2DFront();
}


/// <summary>
/// シーンチェンジチェック
/// </summary>
void GameScene::SceneChangeCheck()
{
	// プレイヤーが勝利 or 敗北でシーンを変更
	if (player_->IsWin() || player_->IsLose()) {
		STMenuManager_->DirectionStart();
	}

	// 演出が終了していれば押せる
	if (STMenuManager_->IsFinish()) {

		// Aボタンを押したらシーントランジション開始
		if (input_->Trigger(PadData::A) || input_->Trigger(DIK_SPACE)) {

			if (STMenuManager_->GetSelect() == MenuSelect::Other) { return; }

			STMenuManager_->EndDirectionStart(); // 終了演出開始
			sceneTransition_->StartFadeOut(); // シーントランジション開始
		}
	}
}

