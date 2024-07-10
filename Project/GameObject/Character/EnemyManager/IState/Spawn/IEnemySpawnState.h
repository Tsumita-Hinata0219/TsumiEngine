#pragma once

#include "../../../../GameObject.h"
#include "../IEnemyState.h"


/* SpawnState派生クラス */
class IEnemySpawnState : public IEnemyState {

public:

	// コンストラクタ
	IEnemySpawnState() {};

	// 初期化、更新、終了
	void Init() override;
	void Update() override;
	void Exit() override;

private:

};

