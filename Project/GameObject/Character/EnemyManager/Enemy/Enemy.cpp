#include "Enemy.h"
#include "GameManager.h"


// 初期化処理
void Enemy::Initialize(Model& modelEnemy, Vector3 pos, Vector3 move)
{
	// モデルの初期化
	model_ = make_unique<Model>();
	(*model_) = modelEnemy;

	// ワールドトランスフォームの初期化	
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	worldTransform_.rotate.y = 6.285f / 2.0f;

	// 加算速度
	velocity_ = Vector3::zero;

	// 移動量の設定
	move_ = move;
}


// 更新処理
void Enemy::Update()
{
	// 移動処理
	Move();

	// ワールド座標の更新
	worldTransform_.UpdateMatrix();
}


// 描画処理
void Enemy::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}


// 移動処理
void Enemy::Move()
{
	// 速度を常に加算
	velocity_ = move_;
	worldTransform_.translate += velocity_;
}
