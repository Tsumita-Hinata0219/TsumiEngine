#pragma once

#include <memory>
#include <functional>

#include "../Bullet/EnemyBullet.h"

#include "GameObject/GameObject.h"


// 前方宣言
class EnemyManager;
class IEnemy;

/* エネミーの射撃処理 */
class EnemyExecuteShot {

public:

	enum Direction {
		Forward,
	};

	enum BulletBehavior {
		Normal,
		Resistant,
		Random,
	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyExecuteShot() = default;
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyExecuteShot() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private:

	/// <summary>
	/// 新しいバレットを追加
	/// </summary>
	void AddNewBullet(EnemyBulletType setType, const Vector3& direction);

	/// <summary>
	/// 前方射撃
	/// </summary>
	void Shot_Forward();


private:

	// バレットの速度
	const float kBulletSpeed_ = 0.25f;

	// 射撃処理のfunction
	std::function<void()> shotFunc_;

	// EnemyManager
	EnemyManager* manager_ = nullptr;

	// オーナーエネミー
	IEnemy* owner_ = nullptr;
};

