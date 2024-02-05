#pragma once

#include "GameObject.h"
#include "Enemy/Enemy.h"


// Playerの前方宣言
class Player;

// GameSceneの前方宣言
class GameScene;

/* EnemyManagerクラス */
class EnemyManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyManager() {};

	/// <summary>
	/// デストラクタ
	/// <summary>
	~EnemyManager() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


#pragma region Get

	/// <summary>
	/// スコープの取得
	/// </summary>
	ScopeVec3 GetScope() { return this->scope_; }

#pragma endregion

#pragma region Set

	/// <summary>
	/// GameSceneの設定
	/// </summary>
	void SetRegisterScene(GameScene* scene) { GameScene_ = scene; }

	/// <summary>
	/// スコープの設定
	/// </summary>
	void SetScope(ScopeVec3 scope) { this->scope_ = scope; }

	/// <summary>
	/// Playerの設定
	/// </summary>
	void SetPlayer(Player* player) { this->player_ = player; }

#pragma endregion


private:

	/// <summary>
	/// 定期的に敵を沸かせる処理
	/// </summary>
	void SpawnEnemysPeriodically();

	/// <summary>
	/// リストの登録
	/// </summary>
	void PushBackEnemy();

	void LoadEnemyPopDate();

	void UpdateEnemyPopCommands();


private:

	// エネミー登録先シーン
	GameScene* GameScene_ = nullptr;

	// プレイヤー
	Player* player_ = nullptr;

	// モデル
	std::unique_ptr<Model> modelEnemy_ = nullptr;

	// スポーン範囲
	ScopeVec3 scope_{};

	// スポーンインターバル
	int intervalFrame_;

	// スポーン時間
	int spawnFrame_;

	// 一回に沸く数
	int instanceEnemyCount_;

	// エネミー最低限数
	int thresholdEnemysCount_;

	uint32_t timer;

	bool res_;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;
};

