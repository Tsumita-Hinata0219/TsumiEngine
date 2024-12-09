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

	/// <summary>
	/// プールに返却前のリセット処理
	/// </summary>
	virtual void Reset() = 0;


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
	SRTN GetSRT() const { return this->trans_.srt; }
	void SetSRT(const SRTN& setSRT) { this->trans_.srt = setSRT; }

	// Scale
	Vector3 GetScale() const { return this->trans_.srt.scale; }
	void SetScale(const Vector3& setScale) { this->trans_.srt.scale = setScale; }

	// Rotate
	Vector3 GetRotate() const { return this->trans_.srt.rotate; }
	void SetRotate(const Vector3& setRotate) { this->trans_.srt.rotate = setRotate; }

	// Translate
	Vector3 GetTranslate() const { return this->trans_.srt.translate; }
	void SetTranslate(const Vector3& setTranslate) { this->trans_.srt.translate = setTranslate; }

	// HP
	virtual uint32_t GetHP() = 0;

#pragma endregion 


protected:

	// 親ポインタ
	EnemyManager* enemyManager_ = nullptr;

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_;

};
