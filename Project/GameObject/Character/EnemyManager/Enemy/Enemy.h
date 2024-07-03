#pragma once

#include <list>
#include <memory>

#include "../../../GameObject.h"

#include "../Bullet/EnemyBullet.h"


// Player前方宣言
class Player;


/* Enemyクラス */
class Enemy : public OBBCollider {

public: // メンバ関数

	// コンストラクタとデストラクタ
	Enemy() {};
	~Enemy() {};

	// 初期化処理　更新処理　描画処理
	void Initialize();
	void Update();
	void Draw3D(Camera* camera);

#pragma region Accessor アクセッサ

	// Playerの設定
	void SetPlayer(Player* setPlayer) { this->player_ = setPlayer; }

	// BulletList
	std::list<std::shared_ptr<EnemyBullet>>& GetBulletList() { return this->bulletList_; }


#pragma endregion 

#pragma region Collision 衝突判定

	// 衝突自コールバック関数
	void OnCollision(uint32_t id) override { id; }
	void OnCollisionWithPlayer();
	void OnCollisionWithPlayerBullet();

	// コライダーのゲッター
	Vector3 GetOBBWorldPos() override { return bodyWt_.GetWorldPos(); }
	Vector3 GetSize() override { return this->size_; }
	Vector3 GetRotate() override { return this->bodyWt_.srt.rotate; }

#pragma endregion 


private:

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


private: // メンバ変数

	// Player
	Player* player_ = nullptr;

	// 本体モデル
	unique_ptr<Model> bodyModel_;

	// 本体座標
	WorldTransform bodyWt_{};

	// サイズ
	Vector3 size_ = { 2.0f, 2.0f, 2.0f };

	// 移動速度
	Vector3 velocity_{};
	float moveVector_ = 0.05f;

	// playerとの最低距離
	float minToPlayer_ = 4.0f;

	// 戦闘状態化のフラグ
	bool isCombatActive_ = false;

	// 戦闘状態になるかならないかの距離の閾値
	float combatTriggerDistance_ = 20.0f;

	// BulletのList配列
	std::list<std::shared_ptr<EnemyBullet>> bulletList_;

	// 射撃するまでのフレーム&インターバル
	int shotFrame_ = 0;
	int kShotInterval_ = 80;
};

