#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"

#include "../Bullet/EnemyBullet.h"


// Player前方宣言
class Player;
class EnemyManager;
struct SRTN;


/* Enemyの基底クラス */
class IEnemy : public IObject {

public:

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IEnemy() = default;

	/// <summary>
	/// Bulletを新しく追加
	/// </summary>
	void AddNewBullet(EnemyBulletType setType, const Vector3& initPos, const Vector3& initVel);


#pragma region Accessor アクセッサ

	// Playerの設定
	virtual void SetPlayer(Player* setPlayer) = 0;

	// EnemyManagerの設定
	virtual void SetEnemyManager(EnemyManager* setManager) { this->enemyManager_ = setManager; }

	// 死亡フラグ
	virtual bool IsDead() const = 0;
	virtual void SetDeadFlag(bool setFlag) = 0;

	// BulletListの取得
	virtual std::list<std::shared_ptr<EnemyBullet>>& GetBulletList() = 0;

	// SRT
	virtual void SetSRT(const SRTN& setSRT) = 0;

	// Scale
	virtual void SetScale(const Vector3& setScale) = 0;

	// Rotate
	virtual void SetRotate(const Vector3& setRotate) = 0;

	// Translate
	virtual void SetTranslate(const Vector3& setTranslate) = 0;

	// HP
	virtual uint32_t GetHP() = 0;

#pragma endregion 


protected:

	// 親ポインタ
	EnemyManager* enemyManager_ = nullptr;
	
};
