#include "EnemyManager.h"
#include "../Player/Player.h"


// 初期化処理
void EnemyManager::Initialize()
{
	// FlagModel
	flagModel_ = make_unique<Model>();
	flagModel_->CreateFromObjAssimpVer("Flag", "Flag");

	// Transformの初期化
	transform_.Initialize();
	transform_.srt.translate.z = 30.0f;

}


// 更新処理
void EnemyManager::Update()
{
	// Transformの更新処理
	transform_.UpdateMatrix();

	// EnemyListの更新処理
	for (std::shared_ptr<Enemy> enemy : enemyList_) {
		enemy->Update();
	}

	// 死亡フラグが立っていたら削除
	enemyList_.remove_if([](std::shared_ptr<Enemy> enemy) {
		if (enemy->IsDead()) {
			enemy.reset();
			return true;
		}
		return false;
		}
	);

#ifdef _DEBUG
	if (ImGui::TreeNode("EnemyManager")) {

		ImGui::Text("Transform");
		ImGui::DragFloat3("Scale", &transform_.srt.scale.x, 0.01f, 0.0f, 20.0f);
		ImGui::DragFloat3("Rotate", &transform_.srt.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &transform_.srt.translate.x, 0.01f);

		ImGui::Text("");
		if (ImGui::Button("AddEnemy")) {
			AddNewEnemy();
		}

		ImGui::TreePop();
	}
#endif // _DEBUG
}


// 描画処理
void EnemyManager::Draw3D(Camera* camera)
{
	// FlagModel
	flagModel_->Draw(transform_, camera);

	// EnemyListの描画
	for (std::shared_ptr<Enemy> enemy : enemyList_) {
		enemy->Draw3D(camera);
	}
}


// 新しいEnemyを追加する
void EnemyManager::AddNewEnemy()
{
	// 新しいEnemyを生成する
	CreateNewEnemy();
}


// 新しいEnemyを生成する
void EnemyManager::CreateNewEnemy()
{
	// 新しいEnemyのインスタンス
	std::shared_ptr<Enemy> newEnemy = std::make_unique<Enemy>();

	// 初期座標
	Vector3 initPos = transform_.GetWorldPos();

	// newEnemyの初期化
	newEnemy->Initialize();
	newEnemy->SetPlayer(player_);
	newEnemy->SetPosition(initPos);

	// リストに追加
	enemyList_.push_back(newEnemy);
}
