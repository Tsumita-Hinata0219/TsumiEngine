#pragma once

#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"


/* PlayerBulletクラス */
class EnemyBullet : public IObject {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	EnemyBullet() { attribute_ = ObjAttribute::ENEMY; };
	~EnemyBullet() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	// 衝突判定コールバック関数
	void onCollision([[maybe_unused]] IObject* object) override;

#pragma region Accessor アクセッサ

	// 座標
	void SetPosition(Vector3 setPos) { this->trans_.srt.translate = setPos; }

	// 速度
	Vector3 GetVelocity() const { return  this->velocity_; }
	void SetVelocity(Vector3 setVel) { this->velocity_ = setVel; }

	// 姿勢
	Vector3 GetRotate() const { return this->trans_.srt.rotate; }
	void SetRotation(Vector3 setRotate) { this->trans_.srt.rotate = setRotate; }
	// 必ずSetVelocityの後に呼び出すこと
	void SetRotationFromVelocity() {
		trans_.srt.rotate.y = std::atan2(velocity_.x, velocity_.z);
		float velZ = std::sqrt((velocity_.x * velocity_.x) + (velocity_.z * velocity_.z));
		float height = -velocity_.y;
		trans_.srt.rotate.x = std::atan2(height, velZ);
	}

	// 死亡フラグ
	bool IsDead() const { return this->isDead_; }

	// Collider
	//OBBCollider* GetOBBCollider() { return this->collider_.get(); }

#pragma endregion 

#pragma region Collision 衝突判定

	// 衝突自コールバック関数
	void OnCollisionWithPlayer();
	void OnCollisionWithPlayerBullet();

#pragma endregion 


private:

	// 移動処理
	void Move();

	// 寿命の処理
	void RemoveAfterlifeTime();


private: // メンバ変数

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};

	// サイズ
	Vector3 size_ = { 2.0f, 2.0f,2.0f };

	// コライダー
	//std::unique_ptr<OBBCollider> collider_;
	Col::Sphere sphere_;

	// 移動速度
	Vector3 velocity_;

	// 寿命
	Timer life_{};

	// 死亡フラグ
	bool isDead_ = false;
};

