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
	GameCamera_.translate = { 0.0f, 5.0f, -40.0f };


	/* ----- Skydome スカイドーム ----- */
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();


	/* ----- Ground グラウンド ----- */
	ground_ = make_unique<Ground>();
	ground_->Initialize();


	/* ----- Player プレイヤー ----- */
	player_ = make_unique<Player>();
	player_->Initialize();
	player_->SetRegisterScene(this); // シーンの設定

	/* ----- Enemy エネミー ----- */
	enemyManager_ = make_unique<EnemyManager>();
	enemyManager_->Initialize();
	enemyManager_->SetPlayer(player_.get());
	enemyManager_->SetRegisterScene(this);
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) {

	// メインカメラ
	GameCamera_.UpdateMatrix();


	/* ----- Skydome スカイドーム ----- */
	skydome_->Update();


	/* ----- Ground グラウンド ----- */
	ground_->Update();


	/* ----- Player プレイヤー ----- */
	player_->Update();
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Update();
	}


	/* ----- Enemy エネミー ----- */
	enemyManager_->Update();
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}

#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("GameCamera");
	ImGui::DragFloat3("Rotate", &GameCamera_.rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &GameCamera_.translate.x, 0.01f);
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
	//skydome_->Draw(GameCamera_);

	/* ----- Ground グラウンド ----- */
	//ground_->Draw(GameCamera_);

	/* ----- Player プレイヤー ----- */
	player_->Draw(GameCamera_);
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


}