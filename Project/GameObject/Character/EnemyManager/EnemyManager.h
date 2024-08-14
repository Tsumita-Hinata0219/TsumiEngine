#pragma once

#include <list>
#include <memory>

#include "../../GameObject.h"

#include "Enemy/Enemy.h"

#include "Enemy/IEnemy.h"
#include "Enemy/Basic/BasicEnemy.h"


// Player前方宣言
class Player;


/* EnemyManagerクラス */
class EnemyManager {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	EnemyManager() {};
	~EnemyManager() {};

	// 初期化処理、更新処理、描画処理
	void Init();
	void Update();
	void Draw3D();

	// 新しいEnemyを追加する
	void AddNewEnemy();

#pragma region Accessor アクセッサ

	// Playerの設定
	void SetPlayer(Player* setPlayer) { this->player_ = setPlayer; }

	// EnemyListの取得
	std::list<std::shared_ptr<Enemy>>& GetEnemyList() { return this->enemyList_; }

#pragma endregion 


private:

	// 新しいEnemyを生成する
	void CreateNewEnemy();
	void CreateBasicEnemy();

	// エネミーカウントチェック
	void EnemyCountCheck();


private: // メンバ変数

	// Player
	Player* player_ = nullptr;

	// FlagModel
	std::unique_ptr<Model> flagModel_;

	// Transform
	Transform transform_{};

	// EnemyのLIst配列
	std::list<std::shared_ptr<Enemy>> enemyList_;
	std::list<std::shared_ptr<IEnemy>> enemys_;


	// Vector3Scope。エネミーの湧き範囲
	ScopeVec3 scope3_{};

	// エネミーの最低数
	int enemyMinInstance_ = 0;

	// エネミーのカウントチェックタイマー
	Timer enemyCountCheckTime_;


	ModelManager* modelManager_ = nullptr;
	std::vector<std::unique_ptr<Model>> spawn_;
	std::vector<Transform> trans_;
	Scope scope_{};
};

