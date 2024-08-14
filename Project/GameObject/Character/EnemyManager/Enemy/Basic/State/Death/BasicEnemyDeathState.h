#pragma once

#include "../../../../../../GameObject.h"
#include "../IBasicEnemyState.h"

#include <memory>
#include <utility>

/* IBasicEnemyStateの派生クラス : 死亡処理 */
class BasicEnemyDeathState : public IBasicEnemyState {

public:

	// コンストラクタ
	BasicEnemyDeathState() {};

	// 初期化、更新、終了
	void Enter(BasicEnemy* owner) override;
	void Update() override;
	void Exit() override;


private:

};