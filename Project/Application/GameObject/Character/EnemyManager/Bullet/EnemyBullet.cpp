#include "EnemyBullet.h"



// 初期化処理
void EnemyBullet::Init()
{
	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/DemoBullet", "DemoBullet.obj");
	model_ = modelManager_->GetModel("DemoBullet");

	// Transformの初期化。座標や姿勢の設定は呼び出し先でaccessorで設定
	trans_.Init();

	// 速度の設定。呼び出し先でaccessorで設定

	// 寿命のタイマーをスタート。10秒で設定
	life_.Init(0.0f, 10.0f * 60.0f);
	life_.Start();

	//// Colliderの初期化
	//collider_ = std::make_unique<OBBCollider>();
	//collider_->Init();
	//collider_->SetSize(size_);
	colComp_ = std::make_unique<CollisionComponent>(this); // コライダーの登録
	colComp_->RegisterCollider(sphere_);
	sphere_.center = trans_.GetWorldPos();
	sphere_.radius = 2.0f;

	colComp_->SetAttribute(ColliderAttribute::Enemy);
	colComp_->Register(sphere_2_);
	sphere_2_.center = trans_.GetWorldPos();
	sphere_2_.radius = 2.0f;
}


// 更新処理
void EnemyBullet::Update()
{
	// Transformの更新処理
	trans_.UpdateMatrix();

	// 移動処理
	Move();

	// 寿命の処理
	RemoveAfterlifeTime();

	// ColliderのSRTの設定
	//collider_->SetSrt(trans_.srt);
	sphere_.center = trans_.GetWorldPos();
	colComp_->UpdateShape(sphere_);
	colComp_->UpdateShape(sphere_);
	sphere_2_.center = trans_.GetWorldPos();
}


// 描画処理
void EnemyBullet::Draw3D()
{
	model_->DrawN(trans_);
}
void EnemyBullet::Draw2DFront() {}
void EnemyBullet::Draw2DBack() {}


// 衝突自コールバック関数
void EnemyBullet::onCollision([[maybe_unused]] IObject* object)
{
	if (object->GetAttribute() == ObjAttribute::PLAYER) {
		isDead_ = true;
	}
}
void EnemyBullet::OnCollisionWithPlayer()
{
	isDead_ = true;
}
void EnemyBullet::OnCollisionWithPlayerBullet()
{
	isDead_ = true;
}


// 移動処理
void EnemyBullet::Move()
{
	trans_.srt.translate += velocity_;
}


// 寿命の処理
void EnemyBullet::RemoveAfterlifeTime()
{
	// 寿命の更新
	life_.Update();

	// タイマーが規定値になったら
	if (life_.IsFinish()) {

		// 死亡フラグを立てる
		isDead_ = true;

		// 寿命のタイマーをクリアしとく
		life_.Clear();
	}
}
