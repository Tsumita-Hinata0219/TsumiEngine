#pragma once

#include "GameObject.h"


/* PlayerBulletクラス */
class PlayerBullet : public OBBCollider {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerBullet() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBullet() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model& modelHD, Vector3 pos, Vector3 vel);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision(uint32_t id) override;


#pragma region Get

	/// <summary>
	/// 死亡フラグの取得
	/// </summary>
	/// <returns></returns>
	bool IsDead() { return this->isDead_; }

	/// <summary>
	/// ワールドトランスフォームの取得
	/// </summary>
	WorldTransform GetWorldTransform() { return this->worldTransform_; }

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	Vector3 GetWorldPosition() override { return this->worldTransform_.GetWorldPos(); }

	/// <summary>
	/// 回転軸の取得
	/// </summary>
	Vector3 GetRotate() override { return this->worldTransform_.rotate; }

	/// <summary>
	/// サイズの取得
	/// </summary>
	Vector3 GetSize() override { return this->size_; }

#pragma endregion


private: // メンバ関数

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// OBBの設定
	/// </summary>
	void SettingOBBProperties();

	/// <summary>
	/// 寿命の処理
	/// </summary>
	void UpdateLifeTimer();


private: // メンバ変数

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_{};

	// 加算速度
	Vector3 velocity_{};

	// 移動量
	Vector3 move_{};

	// サイズ
	Vector3 size_{};

	// 死亡フラグ
	bool isDead_ = false;

	// 寿命
	int32_t kLifeTimer_;
	int32_t lifeTimer_;
};

