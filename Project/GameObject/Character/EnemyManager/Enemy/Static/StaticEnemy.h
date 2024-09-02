#pragma once

#include "../IEnemy.h"

#include "../../../../IObject/IObject.h"
#include "../../../../GameObject.h"

#include "../../Bullet/EnemyBullet.h"


/* 不動型のエネミー */
class StaticEnemy : public IEnemy {

public:

	// コンストラクタ、デストラクタ
	StaticEnemy() {};
	~StaticEnemy() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	// 衝突時コールバック関数
	void OnCollision() override;


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

	// 死亡フラグ
	bool IsDead() const override { return this->isDead_; }
	void SetDeadFlag(bool setFlag) override { this->isDead_ = setFlag; }

	// BulletListの取得
	std::list<std::shared_ptr<EnemyBullet>>& GetBulletList() override { return this->bulletList_; }

	// 座標
	void SetPosition(Vector3 setPos) override { this->trans_.srt.translate = setPos; }

	// Collider
	OBBCollider* GetOBBCollider() override { return this->collider_.get(); }

	// HP
	uint32_t GetHP() override { return this->hp_; }

#pragma endregion 


private:

	// 射撃の処理
	void ExecutexShot();

	// 新しいバレットを生成する
	void CreateNewBullet();


private:

	// プレイヤー
	Player* player_ = nullptr;

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
	std::unique_ptr<OBBCollider> collider_;

	// カラー
	Vector4 modelColor_ = Vector4::one;

	// 回転スピード
	float addRadSpeed_ = 0.0f;

	// HP
	uint32_t hp_ = 0;

	// BulletのList配列
	std::list<std::shared_ptr<EnemyBullet>> bulletList_;

	// 射撃するまでのフレーム&インターバル
	int shotFrame_ = 0;
	int kShotInterval_ = 50;

};

