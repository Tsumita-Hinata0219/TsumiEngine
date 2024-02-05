#include "IEnemyMoveLeaveState.h"
#include "EnemyManager/Enemy/Enemy.h"
#include "Player/Player.h"


// 初期化処理
void IEnemyMoveLeaveState::InitState(Enemy* enemy)
{
	enemy_ = enemy;
}


// 初期化処理
void IEnemyMoveLeaveState::UpdateState()
{
	// 移動処理
	enemy_->MoveLeave();

	// フェーズスタート座標とのベクトル
	toPlayerZ_ = enemy_->GetPlayer()->GetWorldTransform().translate.z - enemy_->GetWorldTransform().translate.z;
	toPlayerZ_ = std::abs(toPlayerZ_);

	// プレイヤーとの距離が指定距離以下になったらステートをチェンジ
	if (toPlayerZ_ >= 80.0f) {
		ChangeState(Approach);
	}
}


// 初期化処理
void IEnemyMoveLeaveState::ExitState()
{


}


// フェーズの変更
void IEnemyMoveLeaveState::ChangeState(int nexrState) 
{
	// 終了処理してシーン変更
	ExitState();
	enemy_->SetMovePhaseNun(nexrState);
}