#pragma once


#include <memory>
#include <functional>
#include <random>

#include "../../Bullet/EnemyBullet.h"
#include "../../Property/EnemyProperty.h"

#include "GameObject/GameObject.h"


// 前方宣言
class EnemyManager;
class IEnemy;

/* エネミーの射撃処理の基底クラス */
class IEnemyExecuteShot {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IEnemyExecuteShot();

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IEnemyExecuteShot() = default;

	/// <summary>
	/// 射撃処理
	/// </summary>
	virtual void Execute(const float bulletSpeed) = 0;

	/// <summary>
	/// 新しいバレットを追加
	/// </summary>
	void AddNewBullet(const Vector3& direction, const float bulletSpeed);

private:

	/// <summary>
	/// 多摩の状態の取得
	/// </summary>
	bool GetBulletBehabir();

private:

	// EnemyManager
	EnemyManager* manager_ = nullptr;

	// オーナーエネミー
	IEnemy* owner_ = nullptr;

	std::mt19937 randEngine_; // ランダムエンジン
	std::uniform_int_distribution<> behabirDist_; // 0 or 1 の分布
	std::uniform_real_distribution<float> directionDist_; // -1 ~ +1 の分布

};
