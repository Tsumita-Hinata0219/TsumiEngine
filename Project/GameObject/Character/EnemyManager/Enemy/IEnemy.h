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
	virtual ~IEnemy() = default;



#pragma region Accessor アクセッサ

	// Playerの設定
	void SetPlayer(Player* setPlayer) { this->player_ = setPlayer; }

	// 死亡フラグ
	bool IsDead() const { return this->isDead_; }
	void SetDeadFlag(bool setFlag) { this->isDead_ = setFlag; }

	// BulletListの取得
	std::list<std::shared_ptr<EnemyBullet>>& GetBulletList() { return this->bulletList_; }



	// 座標
	virtual void SetPosition(Vector3 setPos) = 0;

	// Collider
	virtual OBBCollider* GetOBBCollider() = 0;

#pragma endregion 
	

protected:

	// Player
	Player* player_ = nullptr;

	// 死亡フラグ
	bool isDead_ = false;

	// BulletのList配列
	std::list<std::shared_ptr<EnemyBullet>> bulletList_;

};
