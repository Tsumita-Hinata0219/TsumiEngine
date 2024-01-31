#include "EnemyManager.h"
#include "GameManager.h"


// 初期化処理
void EnemyManager::Initialize()
{
	// モデルの初期化
	modelEnemy_ = make_unique<Model>();
	modelEnemy_->CreateFromObj("Enemy");

	// スポーン範囲
	scope_ = { {-12.0f, 12.0f}, {5.0f, 5.0f}, {100.0f, 200.0f} };

	intervalFrame_ = 250;	   // スポーンインターバル
	spawnFrame_ = 0;		   // スポーンタイマー
	instanceEnemyCount_ = 1;   // 一回に沸く数
	thresholdEnemysCount_ = 3; // マップ内の最低限のエネミー数

	res_ = true;
	timer = 0;

	LoadEnemyPopDate();
}


// 更新処理
void EnemyManager::Update()
{
	if (KeysInput::TriggerKey(DIK_R)) {
		PushBackEnemy();
	}
	
	/*if (res_ == true) {
		timer++;
	}

	if (timer >= 120) {
		timer = 0;
		res_ = false;

		for (int i = 0; i < 2; i++) {
			PushBackEnemy();
		}
	}*/
	UpdateEnemyPopCommands();

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

	newEnemy->SetPlayer(this->player_);
	newEnemy->SetRegisterScene(GameScene_);
	newEnemy->Initialize((*modelEnemy_), newPos, newMov);

	GameScene_->AddEnemyList(newEnemy);
}

void EnemyManager::LoadEnemyPopDate()
{
	// ファイルを開く
	std::ifstream file;
	file.open("Resources/Parameter/enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void EnemyManager::UpdateEnemyPopCommands()
{
	// 1行分の文字列を入れる関数
	std::string line;

	// コマンド実行ループ
	while (std::getline(enemyPopCommands, line)) {

		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// , 区切りで行の先頭文字列を取得
		std::getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {

			PushBackEnemy();
		}
	}
}
