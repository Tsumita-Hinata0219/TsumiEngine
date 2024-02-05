#pragma once

#include "GameObject.h"
#include "EnemyManager/MovePhase/IEnemyMovePhaseState.h"


class IEnemyMoveApproachState : public IEnemyMovePhaseState {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void InitState(Enemy* enemy) override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void UpdateState() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void ExitState() override;

	/// <summary>
	/// フェーズの変更
	/// </summary>
	void ChangeState(int nexrState) override;

private: 

	float toPlayerZ_;
};

