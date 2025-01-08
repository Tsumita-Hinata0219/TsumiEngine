#pragma once

#include <memory>
#include <functional>

#include "../../../GameObject.h"


// 前方宣言
class EnemyManager;
class IEnemy;


/* エネミーの移動処理 */
class EnemyMovement {

public:

	enum class Movement {

	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyMovement(EnemyManager* manager, IEnemy* owner);

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


private:

	// エネミーマネージャー
	EnemyManager* pManager_ = nullptr;

	// エネミー
	IEnemy* pOwner_ = nullptr;

	// 移動関数
	std::function<void()> movementFunc_;

};