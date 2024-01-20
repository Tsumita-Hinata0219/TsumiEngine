#include "IEnemyMoveApproachState.h"
#include "EnemyManager/Enemy/Enemy.h"
#include "Player/Player.h"


// 初期化処理
void IEnemyMoveApproachState::InitState(Enemy* enemy)
{
	enemy_ = enemy;
	enemy_->Attack();
}


// 初期化処理
void IEnemyMoveApproachState::UpdateState()
{
	// 移動処理
	enemy_->MoveApproach();

	// フェーズスタート座標とのベクトル
	toPlayerZ_ = enemy_->GetPlayer()->GetWorldTransform().translate.z - enemy_->GetWorldTransform().translate.z;
	toPlayerZ_ = std::abs(toPlayerZ_);

	// プレイヤーとの距離が指定距離以下になったらステートをチェンジ
	if (toPlayerZ_ <= 10.0f) {
		ChangeState(Leave);
	}
}


// 初期化処理
void IEnemyMoveApproachState::ExitState()
{


}


// フェーズの変更
void IEnemyMoveApproachState::ChangeState(int nexrState)
{
	// 終了処理してシーン変更
	ExitState();
	enemy_->SetMovePhaseNun(nexrState);
}
