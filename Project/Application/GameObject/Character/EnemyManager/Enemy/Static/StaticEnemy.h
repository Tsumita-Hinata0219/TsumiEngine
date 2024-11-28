#pragma once

#include "../IEnemy.h"

#include "../../../../IObject/IObject.h"
#include "../../../../GameObject.h"

#include "../../Bullet/EnemyBullet.h"


/* 不動型のエネミー */
class StaticEnemy : public IEnemy {

public:

	// コンストラクタ、デストラクタ
	StaticEnemy() { attribute_ = ObjAttribute::ENEMY; };
	~StaticEnemy() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	// 衝突判定コールバック関数
	void onCollision([[maybe_unused]] IObject* object) override;


#pragma region Accessor アクセッサ

	// WorldPos
	Vector3 GetWorldPos() { return this->trans_.GetWorldPos(); }

	// SRT
	SRTN GetSRT() const { return this->trans_.srt; }
	void SetSRT(SRTN setSRT) { this->trans_.srt = setSRT; }

	// カラー
	Vector4 GetModelColor() const { return this->modelColor_; }
	void SetModelColor(Vector4 setColor) { this->modelColor_ = setColor; }


	// プレイヤー　
	void SetPlayer(Player* setPlayer) override { this->player_ = setPlayer; }

	// エネミーマネージャー
	void SetEnemyManager(EnemyManager* setManager) override { this->enemyManager_ = setManager; }

	// 死亡フラグ
	bool IsDead() const override { return this->isDead_; }
	void SetDeadFlag(bool setFlag) override { this->isDead_ = setFlag; }

	// BulletListの取得
	std::list<std::shared_ptr<EnemyBullet>>& GetBulletList() override { return this->bulletList_; }

	// 座標
	void SetPosition(Vector3 setPos) override { this->trans_.srt.translate = setPos; }

	// HP
	uint32_t GetHP() override { return this->hp_; }

#pragma endregion 


private:

	// 射撃の処理
	void ExecutexShot();

	// 新しいバレットを生成する
	void CreateNewBullet();
	void CreateNewBullet2();


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

	// ライト
	DirectionalLightData light_{};

	// コライダー
	//std::unique_ptr<OBBCollider> collider_;
	Col::Sphere sphere_;

	// カラー
	Vector4 modelColor_ = Vector4::one;

	// 回転スピード
	float addRadSpeed_ = 0.0f;

	// HP
	uint32_t hp_ = 0;

	// BulletのList配列
	std::list<std::shared_ptr<EnemyBullet>> bulletList_;
	const float kBulletSpeed_ = 0.3f;

	// 射撃するまでのフレーム&インターバル
	int shotFrame_ = 0;
	int kShotInterval_ = 30;

};

