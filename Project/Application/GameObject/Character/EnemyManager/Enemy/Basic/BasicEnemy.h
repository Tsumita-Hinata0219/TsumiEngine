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
	BasicEnemy() { attribute_ = ObjAttribute::ENEMY; };
	~BasicEnemy() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	// 衝突判定コールバック関数
	void onCollision([[maybe_unused]] IObject* object) override;

	// チェンジステート
	void ChangeState(BasicEnemyStateType state) { this->stateNo_ = enum_val(state); }


#pragma region Accessor アクセッサ

	// WorldPos
	Vector3 GetWorldPos() { return this->trans_.GetWorldPos(); }

	// SRT
	SRTN GetSRT() const { return this->trans_.srt; }
	void SetSRT(const SRTN& setSRT) { this->trans_.srt = setSRT; }

	// カラー
	Vector4 GetModelColor() const { return this->modelColor_; }
	void SetModelColor(const Vector4& setColor) { this->modelColor_ = setColor; }


	// プレイヤー　
	void SetPlayer(Player* setPlayer) override { this->player_ = setPlayer; }

	// エネミーマネージャー
	void SetEnemyManager(EnemyManager* setManager) override { this->enemyManager_ = setManager; }

	// 死亡フラグ
	bool IsDead() const override { return this->isDead_; }
	void SetDeadFlag(const bool& setFlag) override { this->isDead_ = setFlag; }

	// BulletListの取得
	std::list<std::shared_ptr<EnemyBullet>>& GetBulletList() override { return this->bulletList_; }

	// 座標
	void SetPosition(const Vector3& setPos) override { this->trans_.srt.translate = setPos; }

	// HP
	uint32_t GetHP() override { return this->hp_; }

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

	// プレイヤー
	Player* player_ = nullptr;

	// エネミーマネージャー
	EnemyManager* enemyManager_ = nullptr;

	// Model
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};

	// サイズ
	Vector3 size_ = { 2.0f, 2.0f, 2.0f };

	// 死亡フラグ
	bool isDead_ = false;

	// Light
	DirectionalLightData light_;

	// コライダー
	//std::unique_ptr<OBBCollider> collider_;
	Col::Sphere sphere_;

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
	float combatTriggerDistance_ = 60.0f;

	// HP
	uint32_t hp_ = 0;

	// BulletのList配列
	std::list<std::shared_ptr<EnemyBullet>> bulletList_;

	// 射撃するまでのフレーム&インターバル
	int shotFrame_ = 0;
	int kShotInterval_ = 40;


	// ステートパターン
	std::vector<std::unique_ptr<IBasicEnemyState>> stateVector_; // ステートコンテナ
	int stateNo_ = 0;        // ステートを管理するクラス
	int currentStateNo_ = 0; // 現在のステート
	int preStateNo_ = 0;	 // 前回のステート
};

