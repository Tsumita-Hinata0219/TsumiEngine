#pragma once

#include "../../../../GameObject.h"
#include "../IEnemyState.h"


/* SpawnState派生クラス */
class IEnemySpawnState : public IEnemyState {

public:

	// 初期化、更新、終了
	void InitState() override;
	void UpdateState() override;
	void ExitState() override;

private:

};

