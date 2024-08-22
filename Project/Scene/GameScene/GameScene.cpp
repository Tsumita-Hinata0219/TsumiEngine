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
	/* ----- JsonManager Jsonマネージャー ----- */
	JsonManager::GetInstance()->Initialize();
	JsonManager::GetInstance()->LoadSceneFile("Json", "kari.json");
	JsonManager::GetInstance()->LoadSceneFile("Json", "nise.json");

	/* ----- CollisionManager コリジョンマネージャー ----- */
	collisionManager_ = std::make_unique<CollisionManager>();

	/* ----- AbsentEffect アブセントエフェクト----- */
	absentEffect_ = std::make_unique<AbsentEffect>();
	absentEffect_->Initialize();

	/* ----- GameSceneUI ゲームシーンUI----- */
	gameSceneUI_ = std::make_unique<GameSceneUI>();
	gameSceneUI_->Init();

	/* ----- Skybox 天箱 ----- */
	skybox_ = std::make_unique<Skybox>();
	skybox_->Init();

	/* ----- Wall 壁 ----- */
	wall_ = std::make_unique<Wall>();
	wall_->Init();

	/* ----- Floor 床 ----- */
	floor_ = std::make_unique<Floor>();
	floor_->Init();

	/* ----- Player プレイヤー ----- */
	player_ = make_unique<Player>();
	player_->Init();

	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->SetPlayer(player_.get());
	enemyManager_->Init();
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state)
{
	/* ----- GameSceneUI ゲームシーンUI----- */
	gameSceneUI_->Update();

	/* ----- Skybox 天箱 ----- */
	skybox_->Update();

	/* ----- Wall 壁 ----- */
	wall_->Update();
	
	/* ----- Floor 床 ----- */
	floor_->Update();

	/* ----- Player プレイヤー ----- */
	player_->Update();

	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_->Update();

	/* ----- Collision 衝突判定 ----- */
	CheckAllCollision();

	/* ----- SceneChange シーンチェンジ ----- */
	// プレイヤーのキルカウントが一定数を超えたらシーンチェンジ
	if (player_->GetKillCount() >= 15) { // <- ここのマジックナンバー後で修正する
		state->ChangeSceneState(new ResultScene);
		return;
	}

#ifdef _DEBUG

	ImGui::Begin("GameScene");

	ImGui::Text("");
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

	/* ----- Wall 壁 ----- */
	wall_->Draw3D();

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

	/* ----- GameSceneUI ゲームシーンUI----- */
	gameSceneUI_->Draw2DFront();

	/* ----- Player プレイヤー ----- */
	player_->Draw2DFront();
}


// 衝突判定処理
void GameScene::CheckAllCollision()
{
	// Player with EnemyBullet
	for (auto& enemy : enemyManager_->GetEnemys()) {
		for (auto& bullet : enemy->GetBulletList()) {
			if (collisionManager_->CheckOBBxOBB(player_->GetOBBCollider(), bullet->GetOBBCollider())) {
				player_->OnCollisionWithEnemyBullet();
				bullet->OnCollisionWithPlayer();
			}
		}
	}

	// PlayerBullet with Enemy
	for (auto& bullet : player_->GetBulletList()) {
		for (auto& enemy : enemyManager_->GetEnemys()) {
			if (collisionManager_->CheckOBBxOBB(bullet->GetOBBCollider(), enemy->GetOBBCollider())) {
				bullet->OnCollisionWithEnemy();
				//enemy->OnCollisionWithPlayerBullet();
			}
		}
	}

	// PlayerBullet with EnemyBullet
	for (auto& playerBullet : player_->GetBulletList()) {
		for (auto& enemy : enemyManager_->GetEnemys()) {
			for (auto& enemyBullet : enemy->GetBulletList()) {
				if (collisionManager_->CheckOBBxOBB(playerBullet->GetOBBCollider(), enemyBullet->GetOBBCollider())) {
					playerBullet->OnCollisionWithEnemyBullet();
					enemyBullet->OnCollisionWithPlayerBullet();
				}
			}
		}
	}
}

