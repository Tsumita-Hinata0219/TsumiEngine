#pragma once

#include "../../../../GameObject.h"
#include "../IEnemyState.h"


/* ApproachState派生クラス */
class IEnemyApproachState : public IEnemyState {

public:

	// 初期化、更新、終了
	void InitState() override;
	void UpdateState() override;
	void ExitState() override;

private:

};