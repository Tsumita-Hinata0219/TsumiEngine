#include "EnemyMovement.h"
#include "../EnemyManager.h"
#include "../Enemy/IEnemy.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyMovement::EnemyMovement(EnemyManager* manager, IEnemy* owner)
{
	this->pManager_ = manager;
	this->pOwner_ = owner;
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
}


/// <summary>
/// 移動関数の設定
/// </summary>
void EnemyMovement::SetMovementFunc(Movement movement)
{
}

