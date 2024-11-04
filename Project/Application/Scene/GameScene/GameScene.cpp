#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {}


/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize()
{
	/* ----- Input 入力 ----- */
	input_ = Input::GetInstance();

	/* ----- JsonManager Jsonマネージャー ----- */
	JsonManager::GetInstance()->Initialize();
	JsonManager::GetInstance()->LoadSceneFile("Json", "kari.json");
	JsonManager::GetInstance()->LoadSceneFile("Json", "nise.json");

	/* ----- CollisionManager コリジョンマネージャー ----- */
	collisionSystem_ = std::make_unique<CollisionSystem>();
	collisionSystem_->Init();

	/* ----- AbsentEffect アブセントエフェクト ----- */
	absentEffect_ = std::make_unique<AbsentEffect>();
	absentEffect_->Init();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_ = make_unique<TestPostEffect>();
	testPostEffect_->Init();

	/* ----- GameSceneUI ゲームシーンUI ----- */
	gameSceneUI_ = std::make_unique<GameSceneUI>();
	gameSceneUI_->Init();

	/* ----- FollowCamera フォローカメラ ----- */
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Init();

	/* ----- StartDirection スタート演出 ----- */
	startDirection_ = std::make_unique<StartDirection>();
	startDirection_->Init();

	/* ----- Skybox 天箱 ----- */
	skybox_ = std::make_unique<Skybox>();
	uint32_t dds = TextureManager::LoadTexture("Texture", "dot.dds");
	skybox_->Init(dds);

	/* ----- Wall 壁 ----- */
	wall_ = std::make_unique<Wall>();
	wall_->Init();

	/* ----- Floor 床 ----- */
	floor_ = std::make_unique<Floor>();
	floor_->Init();

	/* ----- Player プレイヤー ----- */
	player_ = make_unique<Player>();
	player_->Init();
	// プレイヤーにフォローカメラを渡す
	player_->SetFollowCamera(followCamera_.get());
	// フォローカメラにカメラを渡す
	followCamera_->SetPlayer(player_.get());

	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->SetPlayer(player_.get());
	enemyManager_->Init();

	// シーンチェンジにかかる時間。3秒
	sceneChange_.Init(0.0f, 60.0f * 3.0f);
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

	/* ----- FollowCamera フォローカメラ ----- */
	followCamera_->Update();

	/* ----- Skybox 天箱 ----- */
	skybox_->Update();

	/* ----- Wall 壁 ----- */
	wall_->Update();
	
	/* ----- Floor 床 ----- */
	floor_->Update();

	/* ----- StartDirection スタート演出 ----- */
	startDirection_->Update();
	if (!startDirection_->IsFinish()) { return; }
	/*time_++;
	if (time_ >= 2.0f * 60.0f) {
		state->ChangeSceneState(new TitleScene());
		return;
	}*/
	if (input_->Trigger(DIK_RETURN)) {
		state->ChangeSceneState(new TitleScene());
		return;
	}

	/* ----- Player プレイヤー ----- */
	player_->Update();

	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_->Update();

	/* ----- Collision 衝突判定 ----- */
	CheckAllCollision();

#ifdef _DEBUG
	ImGui::Begin("GameScene");
	ImGui::Text("");
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

	/* ----- Player プレイヤー ----- */
	player_->Draw2DFront();

	/* ----- StartDirection スタート演出 ----- */
	startDirection_->Draw2DFront();
}


// シーンチェンジチェック
bool GameScene::SceneChangeCheck(GameManager* state)
{
	// プレイヤーの勝敗条件
	if (player_->IsWin() || player_->IsLose()) {

		if (!sceneChange_.IsActive()) {

			// SceneChangeTimeスタート
			sceneChange_.Start();
		}

		// タイマー更新
		sceneChange_.Update();

		// 終了したらシーンチェンジ
		if (sceneChange_.IsFinish()) {
			state->ChangeSceneState(new ResultScene());
		}

		return true;
	}

	return false;
}


// 衝突判定処理
void GameScene::CheckAllCollision()
{
	// コンポーネントをクリア
	collisionSystem_->ClearComponent();

	// コンポーネントを追加
	collisionSystem_->AAddComponent(player_->GetColComponent());
	for (auto& plaBullet : player_->GetBulletList()) {
		collisionSystem_->AAddComponent(plaBullet->GetColComponent());
	}
	for (auto& enemy : enemyManager_->GetEnemys()) {
		collisionSystem_->AAddComponent(enemy->GetColComponent());
	}
	for (auto& enemy : enemyManager_->GetEnemys()) {
		for (auto& eneBullet : enemy->GetBulletList()) {
			collisionSystem_->AAddComponent(eneBullet->GetColComponent());
		}
	}

	// コリジョン判定を行う
	collisionSystem_->Update();
}