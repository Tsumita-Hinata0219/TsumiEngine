#pragma once

#include "../../../../GameObject.h"
#include "../IEnemyState.h"


/* DeathState派生クラス */
class IEnemyDeathState : public IEnemyState {

public:

	// 初期化、更新、終了
	void InitState() override;
	void UpdateState() override;
	void ExitState() override;

private:

};