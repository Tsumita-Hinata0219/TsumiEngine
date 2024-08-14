#include "BasicEnemyDeathState.h"
#include "../../BasicEnemy.h"



// 初期化処理
void BasicEnemyDeathState::Enter(BasicEnemy* owner)
{
	// Ownerの設定
	owner_ = owner;

}


// 更新処理
void BasicEnemyDeathState::Update()
{

}


// 終了処理
void BasicEnemyDeathState::Exit()
{


}
