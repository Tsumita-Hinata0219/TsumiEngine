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
	//transform_.Init();
	//transform_.srt.translate.z = 30.0f; // 少し奥にずらしておく
	transform_.Init();
	transform_.srt.translate.z = 30.0f;

	// 湧き範囲のスコープ
	scope3_ = {
		{ -6.0f, 6.0f },
		{  0.0f, 0.0f },
		{ -6.0f, 6.0f },
	};

	// エネミーの最低数の設定
	enemyMinInstance_ = 5;

	// エネミーのカウントチェックタイマーの設定。4秒
	enemyCountCheckTime_.Start(0.0f, 240.0f);



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
}


// 更新処理
void EnemyManager::Update()
{
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

	// エネミーカウントチェック
	EnemyCountCheck();

#ifdef _DEBUG
	if (ImGui::TreeNode("EnemyManager")) {

		ImGui::Text("Transform");
		ImGui::DragFloat3("Scale", &transform_.srt.scale.x, 0.01f, 0.0f, 20.0f);
		ImGui::DragFloat3("Rotate", &transform_.srt.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &transform_.srt.translate.x, 0.1f);

		ImGui::Text("");
		if (ImGui::Button("AddEnemy")) {
			AddNewEnemy();
		}
		ImGui::Text("EnemyInstance = %d", int(enemyList_.size()));
		ImGui::Text("CountCheckTime : %.1f / %.1f", enemyCountCheckTime_.GetNowFrame(), enemyCountCheckTime_.GetEndFrame());

		ImGui::TreePop();
	}
#endif // _DEBUG
}


// 描画処理
void EnemyManager::Draw3D()
{
	// FlagModel
	//flagModel_->DrawN(transform_);

	for (int i = 0; i < 3; ++i) {
		spawn_[i]->DrawN(trans_[i]);
	}

	// EnemyListの描画
	for (std::shared_ptr<Enemy> enemy : enemyList_) {
		enemy->Draw3D();
	}
}


// 新しいEnemyを追加する
void EnemyManager::AddNewEnemy()
{
	CreateNewEnemy(); // 新しいEnemyを生成する
}


// 新しいEnemyを生成する
void EnemyManager::CreateNewEnemy()
{
	// 新しいEnemyのインスタンス
	std::shared_ptr<Enemy> newEnemy = std::make_unique<Enemy>();


	int index = int(RandomGenerator::getRandom(scope_));
	
	
	// 初期座標。多少ランダムに湧く
	Vector3 initPos = 
		trans_[index].GetWorldPos() + RandomGenerator::getRandom(scope3_);

	// newEnemyの初期化
	newEnemy->Init();
	newEnemy->SetPlayer(player_);
	newEnemy->SetPosition(initPos);

	// リストに追加
	enemyList_.push_back(newEnemy);
}


// エネミーカウントチェック
void EnemyManager::EnemyCountCheck()
{
	// タイマー更新
	enemyCountCheckTime_.Update(true);

	// タイマー終了でチェック
	if (enemyCountCheckTime_.IsFinish()) {

		// エネミーが一定数以下なら新しく湧くようにする
		if (enemyMinInstance_ >= int(enemyList_.size())) {

			// 最低数との差分
			int shortageCount = enemyMinInstance_ - int(enemyList_.size());

			// 足りない分、新しいEnemyを生成する
			for (int i = 0; i < shortageCount; ++i) {
				CreateNewEnemy();
			}
		}
	}
}
