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

	/* ----- Camera カメラ ----- */
	camera_ = make_unique<Camera>();
	camera_->Initialize();
	camera_->rotate = { 0.2f, 0.0f, 0.0f };
	camera_->translate = { 0.0f, 10.0f, -25.0f };

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

	/* ----- Enemy enemy ----- */
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize();
	enemy_->SetPlayer(player_.get());
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state)
{
	state;

	/* ----- Camera カメラ ----- */
	camera_->UpdateMatrix();

	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Update();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Update();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

	/* ----- Player プレイヤー ----- */
	player_->Update();

	/* ----- Enemy エネミー ----- */
	enemy_->Update();

	/* ----- Collision 衝突判定 ----- */
	CheckAllCollision();

#ifdef _DEBUG

	ImGui::Begin("GameScene");

	ImGui::Text("");
	ImGui::Text("Camera");
	ImGui::DragFloat3("Rotate", &camera_->rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &camera_->translate.x, 0.01f);
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
	//Skydome::GetInstance()->Draw(camera_.get());

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Draw(camera_.get());

	/* ----- Player プレイヤー ----- */
	player_->Draw3D(camera_.get());

	/* ----- Enemy enemy ----- */
	enemy_->Draw3D(camera_.get());
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw()
{
	/* ----- TestPostEffect テストポストエフェクト ----- */
	//testPostEffect_->Draw(camera_.get());
}


// 衝突判定処理
void GameScene::CheckAllCollision()
{
	// Player with EnemyBullet
	for (auto& bullet : enemy_->GetBulletList()) {
		if (collisionManager_->CheckOBBxOBB(player_.get(), bullet.get())) {
			player_->OnCollisionWithEnemyBullet();
			bullet->OnCollisionWithPlayer();
		}
	}

	// PlayerBullet with Enemy
	for (auto& bullet : player_->GetBulletList()) {
		if (collisionManager_->CheckOBBxOBB(bullet.get(), enemy_.get())) {
			bullet->OnCollisionWithEnemy();
			enemy_->OnCollisionWithPlayerBullet();
		}
	}

	// PlayerBullet with EnemyBullet
	for (auto& playerBullet : player_->GetBulletList()) {
		for (auto& enemyBullet : enemy_->GetBulletList()) {
			if (collisionManager_->CheckOBBxOBB(playerBullet.get(), enemyBullet.get())) {
				playerBullet->OnCollisionWithEnemyBullet();
				enemyBullet->OnCollisionWithPlayerBullet();
			}
		}
	}
}

