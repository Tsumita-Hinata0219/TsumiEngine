#include "Ground.h"



// インスタンスの取得
Ground* Ground::GetInstance() {
	static Ground instance;
	return&instance;
}


// 初期化処理
void Ground::Initialize() {

	Ground::GetInstance()->model_ = make_unique<Model>();
	Ground::GetInstance()->model_->CreateFromObj("Ground");
	Ground::GetInstance()->worldTransform_.Initialize();
	Ground::GetInstance()->worldTransform_.scale = { 100.0f, 1.0f, 100.0f };
}


// 更新処理
void Ground::Update() {

	Ground::GetInstance()->worldTransform_.UpdateMatrix();

}


// 描画処理
void Ground::Draw(ViewProjection view) {

	Ground::GetInstance()->model_->Draw(Ground::GetInstance()->worldTransform_, view);
}
