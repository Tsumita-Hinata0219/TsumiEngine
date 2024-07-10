#pragma once

#include "../../../../GameObject.h"
#include "../IEnemyState.h"


/* DeathState派生クラス */
class IEnemyDeathState : public IEnemyState {

public:

	// コンストラクタ
	IEnemyDeathState() {};

	// 初期化、更新、終了
	void Init() override;
	void Update() override;
	void Exit() override;

private:

};