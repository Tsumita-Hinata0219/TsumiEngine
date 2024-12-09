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
	EnemyManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyManager() = default;

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
	/// Jsonで読み込んだ情報を受け取る
	/// </summary>
	void LoadEntityData(const std::vector<std::unique_ptr<EntityData>>& datas);

	/// <summary>
	/// 新しいEnemyBulletを追加する
	/// </summary>
	void AddNewEnemyBullet(EnemyBulletType setType, Vector3 initPos, Vector3 initVel);

#pragma region Accessor アクセッサ

	// Playerの設定
	void SetPlayer(Player* setPlayer) { this->player_ = setPlayer; }

	// 全滅したかのフラグ
	bool IsEliminated() const { return this->isEliminated_; }

	// EnemyListの取得
	std::list<std::shared_ptr<IEnemy>>& GetEnemys() { return this->enemys_; }

#pragma endregion 


private:

	/// <summary>
	/// 全滅したかのチェック
	/// </summary>
	void EliminatedChecker();

	/// <summary>
	/// 新しいEnemyを生成する
	/// </summary>
	void CreateBasicEnemy(const SRTN& setSRT);
	void CreateStaticEnemy(const SRTN& setSRT);

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

	// EnemyのList配列
	std::list<std::shared_ptr<IEnemy>> enemys_;

	// EnemyBulletのObjectPool
	ObjectPool<EnemyBullet> bulletPool_;
	// EnemyBulletのList配列
	std::list<EnemyBullet*> bulletList_;

	// Vector3Scope。エネミーの湧き範囲
	ScopeVec3 scope3_{};

	// エネミーの最低数
	int enemyMinInstance_ = 0;

	// エネミーのカウントチェックタイマー
	Timer enemyCountCheckTime_;

	// エネミーが全滅したかのフラグ
	bool isEliminated_ = false;

	ModelManager* modelManager_ = nullptr;
	std::vector<Transform> trans_;
	Scope scope_{};
};

