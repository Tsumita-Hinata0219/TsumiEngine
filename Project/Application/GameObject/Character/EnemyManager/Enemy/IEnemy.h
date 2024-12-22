#pragma once

#include <list>
#include <memory>
#include <functional>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"

#include "../Bullet/EnemyBullet.h"


// Player前方宣言
class Player;
class EnemyManager;
struct SRT;


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
	SRT GetSRT() const { return this->trans_.srt; }
	void SetSRT(const SRT& setSRT) { this->trans_.srt = setSRT; }

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

	/// <summary>
	/// ヒットリアクション
	/// </summary>
	void HitReaction();


private:

	/// <summary>
	/// スケールのリアクション
	/// </summary>
	void HitReaction_Scale();

	/// <summary>
	/// 色のアクション
	/// </summary>
	void HitReaction_Color();


protected:

	// 親ポインタ
	EnemyManager* enemyManager_ = nullptr;

	// モデル
	std::unique_ptr<Model> model_;

	// 色加算
	ColorAddition colorAdd_{};

	// トランスフォーム
	Transform trans_;

	// 射撃処理
	std::function<void()> executeShot_;

	// ヒットリアクションフラグ
	bool isHitReactioning_ = false;
	// ヒットリアクションタイマー
	Timer hitReactionTimer_{};
	// リアクション時に使用する値
	Vector3 hitReactionScale_{};
	std::pair<float, float> hitReactionColor_;

};
