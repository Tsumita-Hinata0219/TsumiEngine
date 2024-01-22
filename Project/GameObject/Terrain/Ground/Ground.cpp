#include "Ground.h"



// インスタンスの取得
Ground* Ground::GetInstance() 
{
	static Ground instance;
	return&instance;
}


// 初期化処理
void Ground::Initialize() 
{
	this->model_ = make_unique<Model>();
	this->model_->CreateFromObj("Ground");
	this->worldTransform_.Initialize();
	this->worldTransform_.scale = { 100.0f, 1.0f, 100.0f };
	this->size_ = 2.0f * worldTransform_.scale;
	this->size_.y = 0.01f * worldTransform_.scale.y;

	// コライダー
	OBBCollider::SetID(ObjectBit::Terrain);
	OBBCollider::SetCollosionAttribute(ObjectFileter::Terrain);
	OBBCollider::SetCollisionMask(ObjectFileter::Terrain);
}


// 更新処理
void Ground::Update() 
{
	// OBBの設定
	this->SettingOBBProperties();

	// ワールド座標の更新
	this->worldTransform_.UpdateMatrix();
}


// 描画処理
void Ground::Draw(ViewProjection view) 
{
	this->model_->Draw(this->worldTransform_, view);
}


/// 衝突時コールバック関数
void Ground::OnCollision(uint32_t id)
{
	id;
}


// OBBの設定
void Ground::SettingOBBProperties()
{
	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTransform_.rotate);
}