#include "EnemyManager.h"
#include "GameManager.h"


// 初期化処理
void EnemyManager::Initialize()
{
	// モデルの初期化
	modelEnemy_ = make_unique<Model>();
	modelEnemy_->CreateFromObj("Enemy");

	// スポーン範囲
	scope_ = { {-12.0f, 12.0f}, {5.0f, 5.0f}, {5.0f, 50.0f} };

	intervalFrame_ = 250;	   // スポーンインターバル
	spawnFrame_ = 0;		   // スポーンタイマー
	instanceEnemyCount_ = 1;   // 一回に沸く数
	thresholdEnemysCount_ = 3; // マップ内の最低限のエネミー数
}


// 更新処理
void EnemyManager::Update()
{
	if (KeyInput::TriggerKey(DIK_R)) {
		PushBackEnemy();
	}

#ifdef _DEBUG

	if (ImGui::TreeNode("EnemyManager"))
	{
		ImGui::Text("SpawnFlame = %d", spawnFrame_);
		ImGui::Text("SpawnInterval = %d", intervalFrame_);
		ImGui::DragInt("Number ob Spawn", &instanceEnemyCount_, 1.0f, 0, 100);
		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 定期的に敵を沸かせる処理
void EnemyManager::SpawnEnemysPeriodically()
{
	// スポーン時間を加算
	spawnFrame_++;

	// 既定値に達したら
	if (spawnFrame_ >= intervalFrame_) {

		// ０を代入
		spawnFrame_ = 0;

		// 指定数分沸かせる
		for (int i = 0; i < instanceEnemyCount_; i++) {
			PushBackEnemy();
		}
	}
}


// リストの登録
void EnemyManager::PushBackEnemy()
{
	Enemy* newEnemy = new Enemy();
	Vector3 newPos = RandomGenerator::getRandom(scope_.X, scope_.Y, scope_.Z);
	Vector3 newMov = { 0.0f, 0.0f, -0.1f };

	newEnemy->Initialize((*modelEnemy_), newPos, newMov);

	GameScene_->AddEnemyList(newEnemy);
}
