#include "EnemyManager.h"
#include "../Player/Player.h"


// 初期化処理
void EnemyManager::Init()
{
	modelManager_ = ModelManager::GetInstance();

	// FlagModel
	modelManager_->LoadModel("Obj/Flag", "Flag.obj");
	flagModel_ = modelManager_->GetModel("Flag");
	

	// Transformの初期化
	transform_.Init();
	transform_.srt.translate.z = 30.0f;

	// 湧き範囲のスコープ
	scope3_ = {
		{ -6.0f, 6.0f },
		{  0.0f, 0.0f },
		{ -6.0f, 6.0f },
	};

	// エネミーの最低数の設定
	enemyMinInstance_ = 7;

	// エネミーのカウントチェックタイマーの設定。4秒
	enemyCountCheckTime_.Init(0.0f, 240.0f);
	enemyCountCheckTime_.Start();

	// 湧きポイントのフラッグ
	spawn_.resize(3);
	trans_.resize(3);

	for (int i = 0; i < 3; ++i) {
		spawn_[i] = modelManager_->GetModel("Flag");
		trans_[i].Init();
	}
	trans_[0].srt.translate.x = -30.0f;
	trans_[1].srt.translate.z = 30.0f;
	trans_[2].srt.translate.x = 30.0f;

	scope_ = { 0.0f, 2.5f };

	// 最初に何体か湧かせておく
	for (int i = 0; i < 3; ++i) {
		AddBasicEnemy();
		AddStaticEnemy();
	}

	// EnemyListの更新処理
	for (std::shared_ptr<IEnemy> enemy : enemys_) {
		enemy->Update();
	}
}


// 更新処理
void EnemyManager::Update()
{
	// エネミーカウントチェック
	EnemyCountCheck();

	// EnemyListの更新処理
	for (std::shared_ptr<IEnemy> enemy : enemys_) {
		enemy->Update();
	}

	// 死亡フラグが立っていたら削除
	enemys_.remove_if([](std::shared_ptr<IEnemy> enemy) {
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
		ImGui::DragFloat3("Translate", &transform_.srt.translate.x, 0.1f);

		ImGui::Text("");
		if (ImGui::Button("AddBasicEnemy")) {
			AddBasicEnemy();
		}
		if (ImGui::Button("AddStaticnemy")) {
			AddStaticEnemy();
		}
		ImGui::Text("IEnemyInstance = %d", int(enemys_.size()));
		ImGui::Text("CountCheckTime : %.1f / %.1f", enemyCountCheckTime_.GetNowFrame(), enemyCountCheckTime_.GetEndFrame());

		ImGui::TreePop();
	}
#endif // _DEBUG
}


// 描画処理
void EnemyManager::Draw3D()
{
	// FlagModel
	/*flagModel_->DrawN(transform_);
	for (int i = 0; i < 3; ++i) {
		spawn_[i]->DrawN(trans_[i]);
	}*/

	// EnemyListの描画
	for (std::shared_ptr<IEnemy> enemy : enemys_) {
		enemy->Draw3D();
	}
}


// 新しいEnemyを追加する
void EnemyManager::AddBasicEnemy()
{
	CreateBasicEnemy(); // 新しいEnemyを生成する
}
void EnemyManager::AddStaticEnemy()
{
	CreateStaticEnemy(); // 新しいエネミーを生成する
}


// 新しいEnemyを生成する
void EnemyManager::CreateBasicEnemy()
{
	// 新しいEnemyのインスタンス
	std::shared_ptr<BasicEnemy> newEnemy = std::make_unique<BasicEnemy>();

	int index = int(RandomGenerator::getRandom(scope_));

	// 初期座標。多少ランダムに湧く
	Vector3 initPos =
		trans_[index].GetWorldPos() + RandomGenerator::getRandom(scope3_);

	// newEnemyの初期化
	newEnemy->Init();
	newEnemy->SetPlayer(this->player_);
	newEnemy->SetPosition(initPos);

	// リストに追加
	enemys_.push_back(newEnemy);
}
void EnemyManager::CreateStaticEnemy()
{
	// 新しいEnemyのインスタンス
	std::shared_ptr<StaticEnemy> newEnemy = std::make_unique<StaticEnemy>();

	int index = int(RandomGenerator::getRandom(scope_));

	// 初期座標。多少ランダムに湧く
	Vector3 initPos =
		trans_[index].GetWorldPos() + RandomGenerator::getRandom(scope3_);

	// newEnemyの初期化
	newEnemy->Init();
	newEnemy->SetPlayer(this->player_);
	newEnemy->SetPosition(initPos);

	// リストに追加
	enemys_.push_back(newEnemy);
}


// エネミーカウントチェック
void EnemyManager::EnemyCountCheck()
{
	// タイマー更新
	enemyCountCheckTime_.Update(true);

	// タイマー終了でチェック
	if (enemyCountCheckTime_.IsFinish()) {

		// エネミーが一定数以下なら新しく湧くようにする
		if (enemyMinInstance_ >= int(enemys_.size())) {

			// 最低数との差分
			int shortageCount = enemyMinInstance_ - int(enemys_.size());

			// 足りない分、新しいEnemyを生成する
			for (int i = 0; i < shortageCount; ++i) {
				CreateBasicEnemy();
			}
		}
	}
}

