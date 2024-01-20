#include "EnemyBullet.h"



// 初期化処理
void EnemyBullet::Initialize(Model& modelHD, Vector3 pos, Vector3 vel)
{
	// モデルの初期化
	model_ = make_unique<Model>();
	(*model_) = modelHD;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translate = pos;

	// 加算速度
	velocity_ = Vector3::zero;

	// 移動量の設定
	move_ = vel;
}


// 更新処理
void EnemyBullet::Update()
{
	// 移動処理
	Move();

	// ワールド座標の更新
	worldTransform_.UpdateMatrix();
}


// 描画処理
void EnemyBullet::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}


// 移動処理
void EnemyBullet::Move()
{
	// 速度を常に加算
	velocity_ = move_;
	worldTransform_.translate += velocity_;
}
