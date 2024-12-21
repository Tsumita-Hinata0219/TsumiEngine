#include "GameScene.h"
#include "../../GameManager/GameManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() 
{
	input_ = Input::GetInstance();
	CollisionManager_ = CollisionManager::GetInstance();
	absentEffect_ = std::make_unique<AbsentEffect>();
	testPostEffect_ = make_unique<TestPostEffect>();
	gameCamera_ = std::make_unique<GameCamera>();
	startDirection_ = std::make_unique<StartDirection>();
	skybox_ = std::make_unique<SkyboxObj>();
	floor_ = std::make_unique<Floor>();
	boxManager_ = std::make_unique<BoxManager>();
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
	int stageNum = GameData::GetInstance()->Get_StageSelectNum();
	std::string stageJsonFileName = GameData::GetInstance()->GetStageJsonFilePathAt(stageNum);
	JsonManager* jsonManager = JsonManager::GetInstance();
	jsonManager->LoadSceneFile("Json", stageJsonFileName);

	// ──────── AbsentEffect
	absentEffect_->Init();

	// ──────── TestPostEffect
	testPostEffect_->Init();

	// ──────── GameCamera
	gameCamera_->SetCameraType(GameCameraType::TOPDOWN);
	gameCamera_->Init();

	// ──────── StartDirection
	startDirection_->Init();

	// ──────── Skybox
	skybox_->Init();

	// ──────── Floor
	floor_->Init();
	floor_->LoadEntityData(jsonManager->GetEntityData("Floor"));

	// ──────── BoxManager
	boxManager_->Init();
	boxManager_->LoadEntityData(jsonManager->GetEntityData("BarrierBox"));

	// ──────── Player
	player_->Init();
	player_->LoadEntityData(jsonManager->GetEntityData("Player"));

	// ──────── EnemyManager
	enemyManager_->Init();
	enemyManager_->LoadEntityData(jsonManager->GetEntityData("BasicEnemy"));
	enemyManager_->LoadEntityData(jsonManager->GetEntityData("StaticEnemy"));
	enemyManager_->LoadEntityData(jsonManager->GetEntityData("BossEnemy"));

	// ──────── SceneTransition
	STMenuManager_->Init();

	// ──────── StageTransitionMenuManager
	sceneTransition_->Init();
	sceneTransition_->SetState(Cloased);
	sceneTransition_->StartFadeIn();


	jsonManager->Clear();
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// ──────── TestPostEffect
	testPostEffect_->Update();

	// ──────── GameCamera
	gameCamera_->Update();

	// ──────── Skybox
	skybox_->Update();
	
	// ──────── Floor
	floor_->Update();

	// ──────── BoxManager
	boxManager_->Update();

	// ──────── StageTransitionMenuManager
	sceneTransition_->Update();
	// 画面が閉じたらシーン変更
	if (sceneTransition_->GetNowState() == TransitionState::Cloased) {

		// セレクトバーが何を選択したかでチェンジ先シーンを変える
		if (STMenuManager_->GetSelect() == MenuSelect::Back) {
			Manager_->ChangeSceneState(std::make_unique<SelectScene>());
		}
		else if (STMenuManager_->GetSelect() == MenuSelect::Next) {
			GameData::GetInstance()->NextStageSet();
			Manager_->ChangeSceneState(std::make_unique<GameScene>());
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
	// ──────── Player
	player_->Draw2DBack();
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw()
{
	// ──────── Skybox
	skybox_->Draw3D();

	// ──────── Floor
	floor_->Draw3D();

	// ──────── BoxManager
	boxManager_->Draw3D();

	// ──────── EnemyManager
	enemyManager_->Draw3D();

	// ──────── Player
	player_->Draw3D();
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
	// プレイヤー死亡 or エネミー全滅でシーン遷移にに入る
	if (player_->IsDead() || enemyManager_->IsEliminated()) {
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

