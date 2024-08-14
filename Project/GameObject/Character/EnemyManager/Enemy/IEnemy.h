#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"

#include "../Bullet/EnemyBullet.h"

#include "../IState/IEnemyState.h"
#include "../IState/Spawn/IEnemySpawnState.h"
#include "../IState/Approach/IEnemyApproachState.h"
#include "../IState/Death/IEnemyDeathState.h"


// Player前方宣言
class Player;


/* Enemyの基底クラス */
class IEnemy : public IObject {

public:

	// 仮想デストラクタ
	~IEnemy() {};
	
};
