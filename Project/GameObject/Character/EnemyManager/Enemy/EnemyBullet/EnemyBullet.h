#pragma once

#include "GameObject.h"


// Playerの前方宣言
class Player;

/* EnemyBulletクラス */
class EnemyBullet : public OBBCollider {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBullet() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBullet() {};

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
	/// Playerの取得
	/// </summary>
	Player* GetPlayer() { return this->player_; }

	/// <summary>
	/// 死亡フラグの取得
	/// </summary>
	bool IsDead() { return this->isDead_; }

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	Vector3 GetWorldPosition() override { return this->worldTransform_.GetWorldPos(); }

	/// <summary>
	/// Rotateの取得
	/// </summary>
	Vector3 GetRotate() override { return this->worldTransform_.rotate; }

	/// <summary>
	/// Sizeの取得
	/// </summary>
	Vector3 GetSize() override { return this->size_; }

#pragma endregion 

#pragma region Set

	/// <summary>
	/// Playerの設定
	/// </summary>
	void SetPlayer(Player* player) { this->player_ = player; }

#pragma endregion 


private: // メンバ関数

	/// <summary>
	/// プレイヤーへのホーミング処理
	/// </summary>
	void HomingToPlayer();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// OBBの設定
	/// </summary>
	void SettingOBBProperties();


private: // メンバ変数

	// プレイヤー
	Player* player_ = nullptr;

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_{};

	// 加算速度
	Vector3 velocity_{};

	// 移動量
	Vector3 move_{};

	float kbulletSpeed = 1.0f;

	// サイズ
	Vector3 size_{};

	// 死亡フラグ
	bool isDead_ = false;
};

