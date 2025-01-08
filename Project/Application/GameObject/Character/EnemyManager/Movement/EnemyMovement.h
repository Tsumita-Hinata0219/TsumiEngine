#pragma once

#include <memory>
#include <functional>

#include "../../../GameObject.h"


// 前方宣言
class EnemyManager;
class IEnemy;
class Player;


/* エネミーの移動処理 */
class EnemyMovement {

public:

	enum class Movement {
		Static,
		Follow,
		Horizontal,
		Circular,
	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyMovement(EnemyManager* manager, IEnemy* owner, Player* player);

	/// <summary>
	/// デストラク
	/// </summary>
	~EnemyMovement() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Movement movement);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


private:

	/// <summary>
	/// 移動関数の設定
	/// </summary>
	void SetMovementFunc(Movement movement);

	/// <summary>
	/// 不動
	/// </summary>
	void Movement_Static();

	/// <summary>
	/// 追従
	/// </summary>
	void Movement_Follow();

	/// <summary>
	/// 直線移動
	/// </summary>
	void Movement_Horizontal();

	/// <summary>
	/// 円移動
	/// </summary>
	void Movement_Circular();


private:

	// エネミーマネージャー
	EnemyManager* pManager_ = nullptr;

	// エネミー
	IEnemy* pOwner_ = nullptr;

	// プレイヤー
	Player* pPlayer_ = nullptr;

	// 移動関数
	std::function<void()> movementFunc_;

};