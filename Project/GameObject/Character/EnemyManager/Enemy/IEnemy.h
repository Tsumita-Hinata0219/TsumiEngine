#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"

#include "../Bullet/EnemyBullet.h"



// Player前方宣言
class Player;


/* Enemyの基底クラス */
class IEnemy : public IObject {

public:

	// 仮想デストラクタ
	virtual ~IEnemy() = default;

	// 衝突時コールバック関数
	virtual void OnCollision() = 0;



#pragma region Accessor アクセッサ

	// Playerの設定
	virtual void SetPlayer(Player* setPlayer) = 0;

	// 死亡フラグ
	virtual bool IsDead() const = 0;
	virtual void SetDeadFlag(bool setFlag) = 0;

	// BulletListの取得
	virtual std::list<std::shared_ptr<EnemyBullet>>& GetBulletList() = 0;

	// 座標
	virtual void SetPosition(Vector3 setPos) = 0;

	// Collider
	virtual OBBCollider* GetOBBCollider() = 0;

	// HP
	virtual uint32_t GetHP() = 0;

#pragma endregion 
	
};
