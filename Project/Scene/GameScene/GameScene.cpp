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
	/* ----- FileManager ファイルマネージャー ----- */
	FileManager::GetInstance()->LoadJsonFile("Json/", "honmei");

	/* ----- CollisionManager コリジョンマネージャー ----- */
	collisionManager_ = std::make_unique<CollisionManager>();

	/* ----- AbsentEffect アブセントエフェクト----- */
	absentEffect_ = std::make_unique<AbsentEffect>();
	absentEffect_->Initialize();

	/* ----- Camera カメラ ----- */
	cameraResource_.Init();
	cameraResource_.srt.rotate = { 0.2f, 0.0f, 0.0f };
	cameraResource_.srt.translate = { 0.0f, 20.0f, -60.0f };
	cameraManager_ = CameraManager::GetInstance();
	cameraManager_->ReSetData(cameraResource_);

	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Initialize();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Initialize();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_ = make_unique<TestPostEffect>();
	testPostEffect_->Initialize();

	/* ----- Player プレイヤー ----- */
	player_ = make_unique<Player>();
	player_->Initialize();

	/* ----- EnemyManager エネミーマネージャー ----- */
	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->SetPlayer(player_.get());
	enemyManager_->Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state)
{
	state;

	/* ----- Camera カメラ ----- */
	cameraResource_.Update();

	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Update();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Update();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

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
	Skydome::GetInstance()->Draw();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Draw();

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
	/* ----- AbsentEffect アブセントエフェクト----- */
	//absentEffect_->Draw();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Draw(); 
}


// 衝突判定処理
void GameScene::CheckAllCollision()
{
	// Player with EnemyBullet
	for (auto& enemy : enemyManager_->GetEnemyList()) {
		for (auto& bullet : enemy->GetBulletList()) {
			if (collisionManager_->CheckOBBxOBB(player_.get(), bullet.get())) {
				player_->OnCollisionWithEnemyBullet();
				bullet->OnCollisionWithPlayer();
			}
		}
	}

	// PlayerBullet with Enemy
	for (auto& bullet : player_->GetBulletList()) {
		for (auto& enemy : enemyManager_->GetEnemyList()) {
			if (collisionManager_->CheckOBBxOBB(bullet.get(), enemy.get())) {
				bullet->OnCollisionWithEnemy();
				enemy->OnCollisionWithPlayerBullet();
			}
		}
	}

	// PlayerBullet with EnemyBullet
	for (auto& playerBullet : player_->GetBulletList()) {
		for (auto& enemy : enemyManager_->GetEnemyList()) {
			for (auto& enemyBullet : enemy->GetBulletList()) {
				if (collisionManager_->CheckOBBxOBB(playerBullet.get(), enemyBullet.get())) {
					playerBullet->OnCollisionWithEnemyBullet();
					enemyBullet->OnCollisionWithPlayerBullet();
				}
			}
		}
	}
}

