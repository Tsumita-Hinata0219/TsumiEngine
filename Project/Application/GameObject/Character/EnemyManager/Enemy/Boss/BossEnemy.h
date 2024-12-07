#pragma once

#include "../IEnemy.h"

#include "../../../../IObject/IObject.h"
#include "../../../../GameObject.h"

#include "../../Bullet/EnemyBullet.h"


/* ボスエネミー */
class BossEnemy : public IEnemy {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BossEnemy() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossEnemy() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	/// <summary>
	/// 衝突判定コールバック関数
	/// </summary>
	void onCollision([[maybe_unused]] IObject* object) override;

	/// <summary>
	/// プールに返却前のリセット処理
	/// </summary>
	void Reset() override;


#pragma region Accessor アクセッサ

	// WorldPos
	Vector3 GetWorldPos() { return this->trans_.GetWorldPos(); }

	// カラー
	Vector4 GetModelColor() const { return this->modelColor_; }
	void SetModelColor(Vector4 setColor) { this->modelColor_ = setColor; }


	// プレイヤー　
	void SetPlayer(Player* setPlayer) override { this->player_ = setPlayer; }

	// 死亡フラグ
	bool IsDead() const override { return this->isDead_; }
	void SetDeadFlag(bool setFlag) override { this->isDead_ = setFlag; }

	// BulletListの取得
	std::list<std::shared_ptr<EnemyBullet>>& GetBulletList() override { return this->bulletList_; }

	// SRT
	SRTN GetSRT() const { return this->trans_.srt; }
	void SetSRT(const SRTN& setSRT) override { this->trans_.srt = setSRT; }

	// Scale
	void SetScale(const Vector3& setScale) { this->trans_.srt.scale = setScale; }

	// Rotate
	void SetRotate(const Vector3& setRotate) { this->trans_.srt.rotate = setRotate; }

	// Translate
	void SetTranslate(const Vector3& setTranslate) { this->trans_.srt.translate = setTranslate; }

	// HP
	uint32_t GetHP() override { return this->hp_; }

#pragma endregion 


private:


	/// <summary>
	/// 死亡状態に設定
	/// </summary>
	void MarkAsDead();


private:

	// プレイヤー
	Player* player_ = nullptr;

	// Model
	std::unique_ptr<Model> model_;

	// ライト
	DirectionalLightData light_{};

	// トランスフォーム
	Transform trans_{};

	// サイズ
	Vector3 size_ = { 2.0f, 2.0f, 2.0f };

	// 死亡フラグ
	bool isDead_ = false;

	// コライダー
	std::unique_ptr<SphereCollider> sphere_;

	// カラー
	Vector4 modelColor_ = Vector4::one;

	// HP
	uint32_t hp_ = 0;

	// BulletのList配列
	std::list<std::shared_ptr<EnemyBullet>> bulletList_;
	const float kBulletSpeed_ = 0.3f;

	// 射撃するまでのフレーム&インターバル
	int shotFrame_ = 0;
	int kShotInterval_ = 40;

};

