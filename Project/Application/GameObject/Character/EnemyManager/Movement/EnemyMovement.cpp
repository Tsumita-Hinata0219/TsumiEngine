#include "EnemyMovement.h"
#include "../EnemyManager.h"
#include "../Enemy/IEnemy.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyMovement::EnemyMovement(EnemyManager* manager, IEnemy* owner, Player* player)
{
	this->pManager_ = manager;
	this->pOwner_ = owner;
	this->pPlayer_ = player;
}


/// <summary>
/// 初期化処理
/// </summary>
void EnemyMovement::Init(Movement movement)
{
	// 関数設定
	SetMovementFunc(movement);
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyMovement::Update()
{
	// 移動処理
	movementFunc_();
}


/// <summary>
/// 移動関数の設定
/// </summary>
void EnemyMovement::SetMovementFunc(Movement movement)
{
	switch (movement)
	{
	case Movement::Static:
		movementFunc_ = std::bind(&EnemyMovement::Movement_Static, this);
		break;
	case Movement::Follow:
		movementFunc_ = std::bind(&EnemyMovement::Movement_Follow, this);
		break;
	case Movement::Horizontal:
		movementFunc_ = std::bind(&EnemyMovement::Movement_Horizontal, this);
		break;
	case Movement::Circular:
		movementFunc_ = std::bind(&EnemyMovement::Movement_Circular, this);
		break;
	default:
		break;
	}
}


/// <summary>
/// 不動
/// </summary>
void EnemyMovement::Movement_Static()
{
	// 不動型なので、何もしない
}


/// <summary>
/// 追従
/// </summary>
void EnemyMovement::Movement_Follow()
{
}


/// <summary>
/// 直線移動
/// </summary>
void EnemyMovement::Movement_Horizontal()
{
}


/// <summary>
/// 円移動
/// </summary> 
void EnemyMovement::Movement_Circular()
{
}

