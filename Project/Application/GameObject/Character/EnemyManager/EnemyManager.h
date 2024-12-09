#pragma once

#include <list>
#include <memory>

#include "../../GameObject.h"


#include "Enemy/IEnemy.h"
#include "Enemy/Basic/BasicEnemy.h"
#include "Enemy/Static/StaticEnemy.h"

#include "Effect/Interface/IEnemyEffect.h"
#include "Effect/HitEffect/Circle/EnemyHitEffectCircle.h"


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
	/// 新しいEffectを生成する
	/// </summary>
	void CreateEffect(IEnemy* enemyPtr);

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawimGui();

private: // メンバ変数

	// Player
	Player* player_ = nullptr;

	// Transform
	Transform transform_{};

	// EnemyのList配列
	std::list<std::shared_ptr<IEnemy>> enemys_;

	// BulletのPool
	ObjectPool<EnemyBullet> bulletPool_;
	// BulletのList配列
	std::list<EnemyBullet*> bulletList_;

	// EffectのPool
	ObjectPool<EnemyHitEffectCircle> circleEffectPool_;
	// EffectのList配列
	std::list<EnemyHitEffectCircle*> circleEffectList_;

	// エネミーが全滅したかのフラグ
	bool isEliminated_ = false;

};

