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
	jsonManager_ = JsonManager::GetInstance();
	jsonManager_->Initialize();
	jsonManager_->LoadSceneFile("Json", "kari.json");
	jsonManager_->LoadSceneFile("Json", "nise.json");

	/* ----- CollisionManager コリジョンマネージャー ----- */
	collisionManager_ = std::make_unique<CollisionManager>();

	/* ----- AbsentEffect アブセントエフェクト----- */
	absentEffect_ = std::make_unique<AbsentEffect>();
	absentEffect_->Initialize();

	/* ----- Skydome 天球 ----- */
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();

	/* ----- Ground 床 ----- */
	ground_ = std::make_unique<Ground>();
	ground_->Init();

	/* ----- Wall 壁 ----- */
	wall_ = std::make_unique<Wall>();
	wall_->Init();

	/* ----- Floor 床 ----- */
	floor_ = std::make_unique<Floor>();
	floor_->Init();

	/* ----- Building1 建物1 ----- */
	building1_ = std::make_unique<Building1>();
	building1_->Init();

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
	state;

	/* ----- Skydome 天球 ----- */
	skydome_->Update();

	/* ----- Ground 床 ----- */
	ground_->Update();

	/* ----- Wall 壁 ----- */
	wall_->Update();
	
	/* ----- Floor 床 ----- */
	floor_->Update();

	/* ----- Building1 建物1 ----- */
	building1_->Update();

	/* ----- Player プレイヤー ----- */
	player_->Update();

	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_->Update();

	/* ----- Collision 衝突判定 ----- */
	CheckAllCollision();


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

}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw()
{
	/* ----- Skydome 天球 ----- */
	//skydome_->Draw3D();

	/* ----- Ground 床 ----- */
	//ground_->Draw3D();

	/* ----- Wall 壁 ----- */
	wall_->Draw3D();

	/* ----- Floor 床 ----- */
	floor_->Draw3D();

	/* ----- Building1 建物1 ----- */
	building1_->Draw3D();

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
}


// 衝突判定処理
void GameScene::CheckAllCollision()
{
	// Player with EnemyBullet
	for (auto& enemy : enemyManager_->GetEnemyList()) {
		for (auto& bullet : enemy->GetBulletList()) {
			if (collisionManager_->CheckOBBxOBB(player_->GetOBBCollider(), bullet->GetOBBCollider())) {
				player_->OnCollisionWithEnemyBullet();
				bullet->OnCollisionWithPlayer();
			}
		}
	}

	// PlayerBullet with Enemy
	for (auto& bullet : player_->GetBulletList()) {
		for (auto& enemy : enemyManager_->GetEnemyList()) {
			if (collisionManager_->CheckOBBxOBB(bullet->GetOBBCollider(), enemy->GetOBBCollider())) {
				bullet->OnCollisionWithEnemy();
				enemy->OnCollisionWithPlayerBullet();
			}
		}
	}

	// PlayerBullet with EnemyBullet
	for (auto& playerBullet : player_->GetBulletList()) {
		for (auto& enemy : enemyManager_->GetEnemyList()) {
			for (auto& enemyBullet : enemy->GetBulletList()) {
				if (collisionManager_->CheckOBBxOBB(playerBullet->GetOBBCollider(), enemyBullet->GetOBBCollider())) {
					playerBullet->OnCollisionWithEnemyBullet();
					enemyBullet->OnCollisionWithPlayerBullet();
				}
			}
		}
	}
}

