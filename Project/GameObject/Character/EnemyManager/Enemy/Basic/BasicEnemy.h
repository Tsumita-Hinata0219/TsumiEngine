#pragma once

#include "../IEnemy.h"

#include "../../../../IObject/IObject.h"
#include "../../../../GameObject.h"

#include "../../Bullet/EnemyBullet.h"

#include "State/IBasicEnemyState.h"
#include "State/Spawn/BasicEnemySpawnState.h"
#include "State/Idle/BasicEnemyIdleState.h"
#include "State/Approach/BasicEnemyApproachState.h"
#include "State/Death/BasicEnemyDeathState.h"


/* 普通のエネミー */
class BasicEnemy : public IEnemy {

public:

	// コンストラクタとデストラクタ
	BasicEnemy() {};
	~BasicEnemy() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	// 衝突時コールバック関数
	void OnCollision() override;

	// チェンジステート
	void ChangeState(BasicEnemyStateType state) { this->stateNo_ = to_underlying(state); }

#pragma region Accessor アクセッサ

	// WorldPos
	Vector3 GetWorldPos() { return this->trans_.GetWorldPos(); }

	// SRT
	SRTN GetSRT() const { return this->trans_.srt; }
	void SetSRT(SRTN setSRT) { this->trans_.srt = setSRT; }

	// カラー
	Vector4 GetModelColor() const { return this->modelColor_; }
	void SetModelColor(Vector4 setColor) { this->modelColor_ = setColor; }


	// 座標
	void SetPosition(Vector3 setPos) override { this->trans_.srt.translate = setPos; }

	// Collider
	OBBCollider* GetOBBCollider() override { return this->collider_.get(); }

#pragma endregion 

#pragma region Collision 衝突判定

	// 衝突自コールバック関数
	void OnCollisionWithPlayer();
	void OnCollisionWithPlayerBullet();

#pragma endregion 


private:

	// ステートパターン処理
	void FuncStatePattern();

	// 戦闘状態の切り替え処理
	void ToggleCombatState();

	// 移動処理
	void Move();

	// Velocityの計算処理
	void CalcVelocity();

	// 向きの計算処理
	void CalcRotate();

	// 射撃の処理
	void ExecuteShot();

	// 新しいバレットを生成する
	void CreateNewBullet();


private:

	// Model
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};

	// サイズ
	Vector3 size_ = { 2.0f, 2.0f, 2.0f };

	// コライダー
	std::unique_ptr<OBBCollider> collider_;

	// カラー
	Vector4 modelColor_ = Vector4::one;

	// 移動速度
	Vector3 velocity_{};
	float moveVector_ = 0.05f;

	// playerとの最低距離
	float minToPlayer_ = 4.0f;

	// 戦闘状態化のフラグ
	bool isCombatActive_ = false;

	// 戦闘状態になるかならないかの距離の閾値
	float combatTriggerDistance_ = 40.0f;

	// 射撃するまでのフレーム&インターバル
	int shotFrame_ = 0;
	int kShotInterval_ = 80;


	// ステートパターン
	std::vector<std::unique_ptr<IBasicEnemyState>> stateVector_; // ステートコンテナ
	int stateNo_ = 0;        // ステートを管理するクラス
	int currentStateNo_ = 0; // 現在のステート
	int preStateNo_ = 0;	 // 前回のステート
};

