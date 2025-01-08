#pragma once

#include <list>
#include <memory>
#include <functional>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"
#include "Transform/Transform.h"

#include "../ExecuteShot/EnemyExecuteShot.h"
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


#pragma region Accessor アクセッサ

	// Playerの設定
	virtual void SetPlayer(Player* setPlayer) = 0;

	// EnemyManagerの設定
	virtual void SetEnemyManager(EnemyManager* setManager) { this->enemyManager_ = setManager; }

	// 死亡フラグ
	virtual bool IsDead() const = 0;
	virtual void SetDeadFlag(bool setFlag) = 0;

	// SRT
	SRT GetSRT() const { return this->trans_.srt; }
	void SetSRT(const SRT& setSRT) { this->trans_.srt = setSRT; }

	// Scale
	Vector3 GetScale() const { return this->trans_.srt.scale; }
	void SetScale(const Vector3& setScale) { this->trans_.srt.scale = setScale; }

	// Rotate
	Vector3 GetRotate() const { return this->trans_.srt.rotate; }
	void SetRotate(const Vector3& setRotate) { this->trans_.srt.rotate = setRotate; }
	void SetRotate_Y(float setRotate){this->trans_.srt.rotate.y = setRotate;}

	// Translate
	Vector3 GetTranslate() const { return this->trans_.srt.translate; }
	void SetTranslate(const Vector3& setTranslate) { this->trans_.srt.translate = setTranslate; }

	// WorldPos
	Vector3 GetWorldPos() { return this->trans_.GetWorldPos(); }

	// MatWorld
	Matrix4x4 GetMatWorld() const { return this->trans_.matWorld; }

	// HP
	virtual uint32_t GetHP() = 0;

	// ShotProperty
	void SetShotProperty(enemy::ShotFuncData data) { this->shotFuncData_ = data; }

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
	std::unique_ptr<EnemyExecuteShot> exeShot_;
	// 射撃データ
	enemy::ShotFuncData shotFuncData_;

	// ヒットリアクションフラグ
	bool isHitReactioning_ = false;
	// ヒットリアクションタイマー
	Timer hitReactionTimer_{};
	// リアクション時に使用する値
	Vector3 hitReactionScale_{};
	std::pair<float, float> hitReactionColor_;

};
