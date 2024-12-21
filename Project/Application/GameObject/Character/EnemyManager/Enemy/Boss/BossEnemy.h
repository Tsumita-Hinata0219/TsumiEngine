#pragma once

#include "../IEnemy.h"
#include "GameObject/IObject/IObject.h"
#include "Math/MyMath.h"

#include "../../Shield/EnemyShield.h"
#include "../../Bullet/EnemyBullet.h"


/* ボスエネミー */
class BossEnemy : public IEnemy {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BossEnemy() { attribute_ = { Attributes::Category::ENEMY, Attributes::Type::BODY }; };
	
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
	/// 更新処理
	/// </summary>
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	/// <summary>
	/// 衝突判定コールバック関数
	/// </summary>
	void onCollision([[maybe_unused]] IObject* object) override;


#pragma region Accessor アクセッサ

	// プレイヤー　
	void SetPlayer(Player* setPlayer) override { this->player_ = setPlayer; }
	// 死亡フラグ
	bool IsDead() const override { return this->isDead_; }
	void SetDeadFlag(bool setFlag) override { this->isDead_ = setFlag; }

	// BulletListの取得
	std::list<std::shared_ptr<EnemyBullet>>& GetBulletList() override { return this->bulletList_; }

	// HP
	uint32_t GetHP() override { return this->hp_; }

#pragma endregion 


private:

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();



private:

	// プレイヤー
	Player* player_ = nullptr;

	// サイズ
	Vector3 size_ = { 2.0f, 2.0f, 2.0f };

	// 死亡フラグ
	bool isDead_ = false;

	// ライト
	DirectionalLightData light_{};

	// コライダー
	std::unique_ptr<SphereCollider> sphere_;

	// カラー
	Vector4 modelColor_ = Vector4::one;

	// HP
	uint32_t hp_ = 0;

	// シールド　
	std::unique_ptr<EnemyShield> shield_;

	// BulletのList配列
	std::list<std::shared_ptr<EnemyBullet>> bulletList_;

};