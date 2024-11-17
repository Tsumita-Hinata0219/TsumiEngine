#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() 
{
	/* ----- CollisionManager コリジョンマネージャー ----- */
	CollisionManager_ = CollisionManager::GetInstance();
	/* ----- AbsentEffect アブセントエフェクト ----- */
	absentEffect_ = std::make_unique<AbsentEffect>();
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_ = make_unique<TestPostEffect>();
	/* ----- GameSceneUI ゲームシーンUI ----- */
	gameSceneUI_ = std::make_unique<GameSceneUI>();
	/* ----- GameCamera ゲームカメラ ----- */
	gameCamera_ = std::make_unique<GameCamera>();
	/* ----- StartDirection スタート演出 ----- */
	startDirection_ = std::make_unique<StartDirection>();
	/* ----- Skybox 天箱 ----- */
	skybox_ = std::make_unique<Skybox>();
	/* ----- Wall 壁 ----- */
	wall_ = std::make_unique<Wall>();
	/* ----- Floor 床 ----- */
	floor_ = std::make_unique<Floor>();
	/* ----- Player プレイヤー ----- */
	player_ = make_unique<Player>();
	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_ = std::make_unique<EnemyManager>();
	/* ----- SceneTransition シーントランジション ----- */
	sceneTransition_ = SceneTransition::GetInstance();
	/* ----- ClearDirectionManager クリア演出 ----- */
	clearDirectionManager_ = std::make_unique<ClearDirectionManager>();
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
	/* ----- クラスにポインタを渡す ----- */
	// プレイヤーにカメラを渡す
	player_->SetGameCamera(gameCamera_.get());
	// カメラにプレイヤーを渡す
	gameCamera_->SetPlayer(player_.get());
	// エネミーにプレイヤーを渡す
	enemyManager_->SetPlayer(player_.get());


	/* ----- JsonManager Jsonマネージャー ----- */
	JsonManager::GetInstance()->Initialize();
	JsonManager::GetInstance()->LoadSceneFile("Json", "kari.json");
	JsonManager::GetInstance()->LoadSceneFile("Json", "nise.json");

	/* ----- AbsentEffect アブセントエフェクト ----- */
	absentEffect_->Init();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Init();

	/* ----- GameSceneUI ゲームシーンUI ----- */
	gameSceneUI_->Init();

	/* ----- GameCamera ゲームカメラ ----- */
	gameCamera_->SetCameraType(GameCameraType::TOPDOWN);
	gameCamera_->Init();

	/* ----- StartDirection スタート演出 ----- */
	startDirection_->Init();

	/* ----- Skybox 天箱 ----- */
	uint32_t dds = TextureManager::LoadTexture("Texture", "dot.dds");
	skybox_->Init(dds);

	/* ----- Wall 壁 ----- */
	wall_->Init();

	/* ----- Floor 床 ----- */
	floor_->Init();

	/* ----- Player プレイヤー ----- */
	player_->Init();

	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_->Init();

	/* ----- ClearDirectionManager クリア演出 ----- */
	clearDirectionManager_->Init();

	/* ----- SceneTransition シーントランジション ----- */
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
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

	/* ----- GameSceneUI ゲームシーンUI----- */
	gameSceneUI_->Update();

	/* ----- GameCamera ゲームカメラ ----- */
	gameCamera_->Update();

	/* ----- Skybox 天箱 ----- */
	skybox_->Update();

	/* ----- Wall 壁 ----- */
	wall_->Update();
	
	/* ----- Floor 床 ----- */
	floor_->Update();
	
	/* ----- SceneTransition シーントランジション ----- */
	sceneTransition_->Update();
	// 画面が閉じたらシーン変更
	if (sceneTransition_->GetNowState() == TransitionState::Cloased) {
		state->ChangeSceneState(new TitleScene);
		return;
	}
	// シーントランジション中は以下の処理に入らない
	if (sceneTransition_->GetNowState() == TransitionState::Opening ||
		sceneTransition_->GetNowState() == TransitionState::Closing) {
		return;
	}
	SceneChangeCheck();

	/* ----- StartDirection スタート演出 ----- */
	startDirection_->Update();
	if (!startDirection_->IsFinish()) {
		return;
	}

	/* ----- ClearDirectionManager クリア演出 ----- */
	clearDirectionManager_->Update();
	if (clearDirectionManager_->GetState() == ClearDirectionState::Finished) {
		return;
	}

	/* ----- Player プレイヤー ----- */
	player_->Update();

	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_->Update();

	/* ----- Collision 衝突判定 ----- */
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
	/* ----- GameSceneUI ゲームシーンUI----- */
	gameSceneUI_->Draw2DBack();

	/* ----- Player プレイヤー ----- */
	player_->Draw2DBack();
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw()
{
	/* ----- Skybox 天箱 ----- */
	skybox_->Draw();

	/* ----- Floor 床 ----- */
	floor_->Draw3D();

	/* ----- Player プレイヤー ----- */
	player_->Draw3D();

	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_->Draw3D();
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw()
{
	absentEffect_->Draw();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Draw();

	/* ----- GameSceneUI ゲームシーンUI----- */
	gameSceneUI_->Draw2DFront();

	/* ----- StartDirection スタート演出 ----- */
	startDirection_->Draw2DFront();

	/* ----- ClearDirectionManager クリア演出 ----- */
	clearDirectionManager_->Draw2DFront();

	/* ----- Player プレイヤー ----- */
	player_->Draw2DFront();

	/* ----- SceneTransition シーントランジション ----- */
	sceneTransition_->Draw2DFront();
}


// シーンチェンジチェック
void GameScene::SceneChangeCheck()
{
	// プレイヤーが勝利するか敗北するかすれば
	// シーンを変更する
	if (player_->IsWin() || player_->IsLose()) {
		clearDirectionManager_->DirectionStart();
	}
}

