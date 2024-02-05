#pragma once

#include "GameObject.h"

#include "EnemyBullet/EnemyBullet.h"

#include "EnemyManager/MovePhase/IEnemyMovePhaseState.h"
#include "EnemyManager/MovePhase/Approach/IEnemyMoveApproachState.h"
#include "EnemyManager/MovePhase/Leave/IEnemyMoveLeaveState.h"


// Playerの前方宣言
class Player;

// GameSceneの前方宣言
class GameScene;

/* Enemyクラス */
class Enemy : public OBBCollider {

public: // エネミー本体 : メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model& modelEnemy, Vector3 pos, Vector3 move);

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

	/// <summary>
	/// 移動処理
	/// </summary>
	void MoveApproach();
	void MoveLeave();

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Attack();


#pragma region Get

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	WorldTransform GetWorldTransform() { return this->worldTransform_; }

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
	/// 回転軸の取得
	/// </summary>
	Vector3 GetRotate() override { return this->worldTransform_.rotate; }

	/// <summary>
	/// サイズの取得
	/// </summary>
	Vector3 GetSize() override { return this->size_; }

#pragma endregion 

#pragma region Set

	/// <summary>
	/// Playerの設定
	/// </summary>
	void SetPlayer(Player* player) { this->player_ = player; }

	/// <summary>
	/// GameSceneの設定
	/// </summary>
	void SetRegisterScene(GameScene* scene) { GameScene_ = scene; }

	/// <summary>
	/// 死亡フラグの設定
	/// </summary>
	void SetIsDead(bool flag) { this->isDead_ = flag; }

#pragma endregion 

private: // エネミー本体 : メンバ関数

	/// <summary>
	/// OBBの設定
	/// </summary>
	void SettingOBBProperties();


private: // エネミー本体 : メンバ変数

	// プレイヤー
	Player* player_ = nullptr;

	// モデル
	unique_ptr<Model> model_ = nullptr;

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


public: // エネミーバレット : メンバ関数

	/// <summary>
	/// バレットの初期化処理
	/// </summary>
	void BulletInit();

	/// <summary>
	/// バレットの更新処理
	/// </summary>
	void BulletUpdate();

private: // エネミーバレット : メンバ関数

	/// <summary>
	/// バレットの進行方向の計算
	/// </summary>
	Vector3 CalcDirection();

	/// <summary>
	/// バレットリストの登録
	/// </summary>
	void PushBackBulletList();

private: // エネミーバレット : メンバ変数

	// 登録先シーン
	GameScene* GameScene_ = nullptr;

	// モデル
	std::unique_ptr<Model> modelBullet_ = nullptr;

	// 移動速度
	Vector3 bulletVelocity_ = Vector3::zero;

	// バレットの速度
	const float kBulletSpeed_ = 1.0f;

	// 一回に撃つ弾の数
	int bulletsPerSpanw_;

	// 射撃タイマーとインターバル
	int32_t FireInterval_;
	int32_t FireTimer_;


public: // ムーブフェーズ : メンバ関数

#pragma region Get

	/// <summary>
	/// ムーブフェーズの取得
	/// </summary>
	int GetMovePhaseNum() { return this->movePhaseNum_; }

#pragma endregion 

#pragma region Set

	/// <summary>
	/// ムーブフェーズの設定
	/// </summary>
	void SetMovePhaseNun(int nextPhase) { this->movePhaseNum_ = nextPhase; }

#pragma endregion 

private: // ムーブフェーズ : メンバ関数

	/// <summary>
	/// ムーブフェーズの初期化処理
	/// </summary>
	void MovePhaseInit();

	/// <summary>
	/// ムーブフェーズの更新処理
	/// </summary>
	void MovePhaseUpdate();

private: // ムーブフェーズ : メンバ変数

	// ムーブフェーズ
	std::unique_ptr<IEnemyMovePhaseState> movePhaseArr_[2];
	int movePhaseNum_ = 0;
	int currMovePhase_;
	int prevMovePhase_;

};
