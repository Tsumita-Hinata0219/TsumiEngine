#pragma once

#include <memory>
#include <functional>

#include "GameObject/GameObject.h"


// 前方宣言
class EnemyMaanger;
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

	// 射撃処理のfunction
	std::function<void()> shotFunc_;

	// EnemyManager
	EnemyMaanger* manager_ = nullptr;

	// オーナーエネミー
	IEnemy* owner_ = nullptr;
};

