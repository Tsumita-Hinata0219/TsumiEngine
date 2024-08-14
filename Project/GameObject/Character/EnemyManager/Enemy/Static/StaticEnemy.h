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

	// 回転スピード
	float addRadSpeed_ = 0.0f;



};

