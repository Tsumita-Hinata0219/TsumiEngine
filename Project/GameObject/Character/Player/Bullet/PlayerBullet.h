#pragma once


#include <memory>

#include "GameObject.h"


/* PlayerBulletクラス */
class PlayerBullet {

public:

	// コンストラクタ、デストラクタ
	PlayerBullet() {};
	~PlayerBullet() {};

	// 初期化処理、更新処理、描画処理
	void Initialize(Model* SetModel);
	void Update();
	void Draw3D(Camera* camera);

#pragma region Accessor アクセッサ

	// 座標
	Vector3 GetPosition() { return this->bulletWt_.GetWorldPos(); }
	void SetPosition(Vector3 setPos) { this->bulletWt_.srt.translate = setPos; }

	// 速度
	Vector3 GetVelocity() const { return  this->velocity_; }
	void SetVelocity(Vector3 setVel) { this->velocity_ = setVel; }

	// 姿勢
	Vector3 GetRotate() const { return this->bulletWt_.srt.rotate; }
	void SetRotation(Vector3 setRotate) { this->bulletWt_.srt.rotate = setRotate; }
	// 必ずSetVelocityの後に呼び出すこと
	void SetRotationFromVelocity() {
		bulletWt_.srt.rotate.y = std::atan2(velocity_.x, velocity_.z);
		float velZ = std::sqrt((velocity_.x * velocity_.x) + (velocity_.z * velocity_.z));
		float height = -velocity_.y;
		bulletWt_.srt.rotate.x = std::atan2(height, velZ);
	}

	// 死亡フラグ
	bool IsDead() const { return this->isDead_; }

#pragma endregion 


private:

	// 移動処理
	void Move();

	// 寿命の処理
	void RemoveAfterlifeTime();


private:

	// 本体モデル
	unique_ptr<Model> bulletModel_ = nullptr;

	// 本体座標
	WorldTransform bulletWt_{};

	// 移動速度
	Vector3 velocity_;

	// 寿命
	Timer life_{};

	// 死亡フラグ
	bool isDead_ = false;
};

