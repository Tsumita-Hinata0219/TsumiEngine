#include "Player.h"



// 初期化処理
void Player::Initialize() 
{
	// モデルの初期化
	model_ = make_unique<Model>();
	model_->CreateFromObj("Player");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translate.y = 5.0f;

	// 加算速度
	velocity_ = Vector3::zero;

	// 移動量
	move_ = Vector3::zero;
	moveSpeed_ = 0.5f;
}


// 更新処理
void Player::Update()
{
	// 移動処理
	Move();


	// ワールド座標の更新
	worldTransform_.UpdateMatrix();




#ifdef _DEBUG

	if (ImGui::TreeNode("Player")) 
	{
		ImGui::DragFloat3("Scale", &worldTransform_.scale.x, 0.01f);
		ImGui::DragFloat3("Rotate", &worldTransform_.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &worldTransform_.translate.x, 0.01f);
		ImGui::DragFloat3("Velocity", &velocity_.x, 0.01f);
		ImGui::DragFloat3("Move", &move_.x, 0.01f);
		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void Player::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);

}


// 移動処理
void Player::Move() {

	// 見えない壁。移動処理限界
	worldTransform_.translate.y = min(worldTransform_.translate.y, vhInfo.up);
	worldTransform_.translate.y = max(worldTransform_.translate.y, vhInfo.down);
	worldTransform_.translate.x = min(worldTransform_.translate.x, vhInfo.left);
	worldTransform_.translate.x = max(worldTransform_.translate.x, vhInfo.right);

	// move_は毎フレーム０代入
	// move_を増やすことで移動
	move_ = Vector3::zero;
	velocity_ = Vector3::zero;

	if (KeyInput::PressKeys(DIK_W)) {
		move_.y = moveSpeed_;
	}
	if (KeyInput::PressKeys(DIK_A)) {
		move_.x = -moveSpeed_;
	}
	if (KeyInput::PressKeys(DIK_S)) {
		move_.y = -moveSpeed_;
	}
	if (KeyInput::PressKeys(DIK_D)) {
		move_.x = moveSpeed_;
	}

	// 速度を常に加算
	velocity_ += move_;
	worldTransform_.translate += velocity_;
}

