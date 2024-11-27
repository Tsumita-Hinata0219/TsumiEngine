#pragma once

#include <list>
#include <memory>

#include "../../GameObject.h"


#include "Enemy/IEnemy.h"
#include "Enemy/Basic/BasicEnemy.h"
#include "Enemy/Static/StaticEnemy.h"


// Player前方宣言
class Player;


/* EnemyManagerクラス */
class EnemyManager {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyManager() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyManager() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw3D();

	/// <summary>
	/// 新しいEnemyを追加する
	/// </summary>
	void AddNewBasicEnemy();
	void AddNewStaticEnemy();

	/// <summary>
	/// 新しいEnemyBulletを追加する
	/// </summary>
	void AddNewEnemyBullet(EnemyBulletType setType, Vector3 initPos, Vector3 initVel);

#pragma region Accessor アクセッサ

	// Playerの設定
	void SetPlayer(Player* setPlayer) { this->player_ = setPlayer; }

	// EnemyListの取得
	std::list<std::shared_ptr<IEnemy>>& GetEnemys() { return this->enemys_; }

#pragma endregion 


private:

	/// <summary>
	/// エネミーカウントチェック
	/// </summary>
	void EnemyCountCheck();

	/// <summary>
	/// 新しいEnemyを生成する
	/// </summary>
	void CreateBasicEnemy();
	void CreateStaticEnemy();

	/// <summary>
	/// 新しいEnemyBulletを生成する
	/// </summary>
	void CreateEnemyBullet(EnemyBulletType setType, Vector3 initPos, Vector3 initVel);

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawimGui();

private: // メンバ変数

	// Player
	Player* player_ = nullptr;

	// FlagModel
	std::unique_ptr<Model> flagModel_;

	// Transform
	Transform transform_{};

	// EnemyのLIst配列
	std::list<std::shared_ptr<IEnemy>> enemys_;

	// EnemyBulletのList配列
	std::list<std::shared_ptr<EnemyBullet>> bulletList_;


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

