#include "GameScene.h"



/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {

	/* ----- プレイヤー Player ----- */
	for (PlayerBullet* bullet : playerBullets_) {
		delete bullet;
	}

	/* ----- Enemy エネミー ----- */
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
}


/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize() {

	// メインカメラ
	GameCamera_.Initialize();


	/* ----- CollisionManager コリジョンマネージャー ----- */
	collisionManager_ = make_unique<CollisionManager>();


	/* ----- Skydome スカイドーム ----- */
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();


	/* ----- Ground グラウンド ----- */
	ground_ = make_unique<Ground>();
	ground_->Initialize();


	/* ----- Player プレイヤー ----- */
	player_ = make_unique<Player>();
	Vector3 initPlayerTranslate = { 0.0f, -3.0f, 30.0f };
	player_->Initialize(initPlayerTranslate);
	player_->SetRegisterScene(this);


	/* ----- Enemy エネミー ----- */
	enemyManager_ = make_unique<EnemyManager>();
	enemyManager_->Initialize();
	enemyManager_->SetPlayer(player_.get());
	enemyManager_->SetRegisterScene(this);


	/* ----- DebugCamera デバッグカメラ----- */
	debugCamera_ = make_unique<DebugCamera>();
	debugCamera_->Initialize();
	debugCamera_->SetIsActive(false);


	/* ----- RailCamera レールカメラ----- */
	railCamera_ = make_unique<RailCamera>();
	Vector3 initRotate = { 0.0f, 0.0f, 0.0f };
	Vector3 initTranslate = { 0.0f, 9.0f, 0.0f };
	railCamera_->Initialize(initRotate, initTranslate + player_->GetWorldPosition());


	/* ----- Parent 親子関係ペアレント ----- */
	player_->SetParent(&railCamera_->GetWorldTransform());
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) {

	/* ----- GameCamera ゲームカメラ----- */
	GameCamera_.UpdateMatrix();
	if (debugCamera_->GetIsActive()) {

		// デバッグカメラの更新処理
		debugCamera_->Update();
		GameCamera_ = debugCamera_->GetViewProjection();
	}
	else {
		// デバッグカメラの更新処理
		railCamera_->Update();
		GameCamera_ = railCamera_->GetViewProjection();
	}


	/* ----- Skydome スカイドーム ----- */
	skydome_->Update();


	/* ----- Ground グラウンド ----- */
	ground_->Update();


	/* ----- Player プレイヤー ----- */
	player_->Update();
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Update();
	}
	playerBullets_.remove_if([](PlayerBullet* plaBul) {
		if (plaBul->IsDead()) {
			delete plaBul;
			return true;
		}
		return false;
		});


	/* ----- Enemy エネミー ----- */
	enemyManager_->Update();
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}
	enemyBullets_.remove_if([](EnemyBullet* eneBul) {
		if (eneBul->IsDead()) {
			delete eneBul;
			return true;
		}
		return false;
	});


	/* ----- CollisionManager コリジョンマネージャー ----- */
	CheckAllCollision();



#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("GameCamera");
	ImGui::DragFloat3("Rotate", &GameCamera_.rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &GameCamera_.translate.x, 0.01f);
	ImGui::Text("PlayerBulletList = %d", int32_t(playerBullets_.size()));
	ImGui::Text("EnemyList = %d", int32_t(enemys_.size()));
	ImGui::Text("EnemyBulletList = %d", int32_t(enemyBullets_.size()));
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void GameScene::BackSpriteDraw() {


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw() {

	/* ----- Skydome スカイドーム ----- */
	skydome_->Draw(GameCamera_);

	/* ----- Ground グラウンド ----- */
	ground_->Draw(GameCamera_);

	/* ----- Player プレイヤー ----- */
	player_->Draw3D(GameCamera_);
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Draw(GameCamera_);
	}

	/* ----- Enemy エネミー ----- */
	for (Enemy* enemy : enemys_) {
		enemy->Draw(GameCamera_);
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(GameCamera_);
	}
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() {

	/* ----- Player プレイヤー ----- */
	player_->Draw2DFront(GameCamera_);
}


/// <summary>
/// 衝突判定と応答
/// </summary>
void GameScene::CheckAllCollision() {

	// 登録されたコライダーリストをクリアする
	collisionManager_->ClliderClear();

	// コライダーをリストに登録する
	collisionManager_->AddOBBColliders(ground_.get());
	collisionManager_->AddOBBColliders(player_.get());
	for (PlayerBullet* bullet : playerBullets_) {
		collisionManager_->AddOBBColliders(bullet);
	}
	for (Enemy* enemy : enemys_) {
		collisionManager_->AddOBBColliders(enemy);
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		collisionManager_->AddOBBColliders(bullet);
	}

	// すべてのコライダーに対して衝突を検出
	collisionManager_->CheckAllCollision();
}