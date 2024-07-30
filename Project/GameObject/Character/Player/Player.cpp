#include "Player.h"



// 初期化処理
void Player::Init()
{
	// Inputクラス
	input_ = Input::GetInstance();

	// カメラ
	cameraManager_ = CameraManager::GetInstance();
	camera_.Init();
	camera_.srt.rotate = { 0.2f, 0.0f, 0.0f };
	camera_.srt.translate = { 0.0f, 20.0f, -60.0f };
	cameraManager_->ReSetData(camera_);
	// プレイヤーからのオフセット
	cameraOffset_ = { 0.0f, 2.0f, -10.0f };


	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Player", "Player.obj");
	model_ = modelManager_->GetModel("Player");

	// BodyTransformの初期化
	trans_.Init();

	// Colliderの初期化
	collider_ = std::make_unique<OBBCollider>();
	collider_->Init();
	collider_->SetSize(size_);
}


// 更新処理
void Player::Update()
{
	// カメラの更新処理
	camera_.Update();

	// カメラ操作
	CameraOperation();

	// Transformの更新処理
	trans_.UpdateMatrix();

	// 移動処理
	Move();

	// プレイヤー本体の姿勢処理
	CalcBodyRotate();

	// 射撃の処理
	ExecuteShot();

	// Bulletの更新処理
	for (std::shared_ptr<PlayerBullet> bullet : bulletList_) {
		bullet->Update();
	}

	// 死亡フラグが立っていたら削除
	bulletList_.remove_if([](std::shared_ptr<PlayerBullet> bullet) {
		if (bullet->IsDead()) {
			bullet.reset();
			return true;
		}
		return false;
		}
	);

	// ColliderのSRTの設定
	collider_->SetSrt(trans_.srt);

#ifdef _DEBUG
	if (ImGui::TreeNode("Camera")) {
		camera_.DrawImGui();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Player")) {

		trans_.DrawImGui();
		ImGui::Text("");
		ImGui::Text("ShotFrame = %d", shotPressFrame_);

		ImGui::Text("");
		light_.DrawImGui();

		ImGui::Text("");
		ImGui::Text("Stick");
		ImGui::DragFloat2("R_Stick", &R_StickInput_.x, 0.0f);
		ImGui::DragFloat2("L_Stick", &L_StickInput_.x, 0.0f);

		ImGui::TreePop();
	}
#endif // _DEBUG
}


// 描画処理
void Player::Draw3D()
{
	// BodyModelの描画
	model_->SetLightData(light_);
	model_->DrawN(trans_);

	// Bulletsの描画
	for (std::shared_ptr<PlayerBullet> bullet : bulletList_) {
		bullet->Draw3D();
	}
}
void Player::Draw2DBack() {}
void Player::Draw2DFront() {}


// 衝突自コールバック関数
void Player::OnCollisionWithEnemy()
{


}
void Player::OnCollisionWithEnemyBullet()
{


}


// 移動処理
void Player::Move()
{
	// velocityは0で毎フレーム初期化
	velocity_ = Vector3::zero;

	// キーの処理
	if (input_->Press(DIK_W))
	{
		velocity_.z = moveVector_;
	};
	if (input_->Press(DIK_A))
	{
		velocity_.x = -moveVector_;
	};
	if (input_->Press(DIK_S))
	{
		velocity_.z = -moveVector_;
	};
	if (input_->Press(DIK_D))
	{
		velocity_.x = moveVector_;
	};

	// パッドの処理
	if (input_->GetLStick().x <= -0.3f)
	{
		velocity_.x = -1.0f;
	}
	if (input_->GetLStick().x >= 0.3f)
	{
		velocity_.x = 1.0f;
	}
	if (input_->GetLStick().y <= -0.3f)
	{
		velocity_.z = -1.0f;
	}
	if (input_->GetLStick().y >= 0.3f)
	{
		velocity_.z = 1.0f;
	}

	// 正規化
	if (velocity_.x != 0.0f || velocity_.z != 0.0f) {
		float length = Length({ velocity_.x, velocity_.z });
		velocity_.x /= length;
		velocity_.z /= length;
	}

	// velocityに速度を掛けて座標に加算
	trans_.srt.translate += (velocity_ * moveVector_);
}


// プレイヤー本体の姿勢処理
void Player::CalcBodyRotate()
{
	// 回転に使うVector2
	Vector2 stickInput{};

	// 射撃ボタン押下時はRStickの入力を取得
	if (input_->Press(DIK_SPACE) || input_->Press(PadData::RIGHT_SHOULDER)) {
		stickInput = input_->GetRStick(); // RStick
	}
	else {
		stickInput = input_->GetLStick(); // LStick
	}

	// stick入力が一定範囲を超えている場合、角度を更新
	if (std::abs(stickInput.x) > 0.2f || std::abs(stickInput.y) > 0.2f) {

		// Y軸周り角度(θy)
		trans_.srt.rotate.y = std::atan2(stickInput.x, stickInput.y);
	}
}


// 射撃処理
void Player::ExecuteShot()
{
	// キーorボタン押下でタイマーをデクリメント
	if (input_->Press(DIK_SPACE) || input_->Press(PadData::RIGHT_SHOULDER)) {

		shotPressFrame_--;

		if (shotPressFrame_ <= 0) {
			// 0以下でタイマー再設定
			shotPressFrame_ = kShotInterval_;
			// バレット生成
			CreateNewBullet();
		}
	}
	// キーorボタンを離したら、最初の1発目がすぐ出るように1フレームを入れておく
	else if (input_->Release(DIK_SPACE) || input_->Release(PadData::RIGHT_SHOULDER)) {
		
		shotPressFrame_ = 1;
	}
}


// 新しいバレットを生成する
void Player::CreateNewBullet()
{
	// newBulletのインスタンス
	std::shared_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();

	// 初期座標
	Vector3 initPos = trans_.GetWorldPos();
	// 初期速度
	Vector3 initVel = Vector3::oneZ;
	initVel = TransformNormal(initVel, trans_.matWorld);

	// newBulletの初期化
	newBullet->Init();
	newBullet->SetPosition(initPos);
	newBullet->SetVelocity(initVel);
	newBullet->SetRotationFromVelocity();

	// リストに追加
	bulletList_.push_back(newBullet);
}


// カメラ操作
void Player::CameraOperation()
{
	// カメラの回転処理
	CameraRotate();
}


// カメラの回転処理
void Player::CameraRotate()
{
	// stickの入力を受け取る
	R_StickInput_ = input_->GetRStick();

	// stick入力が一定範囲を超えている場合、角度を更新
	if (std::abs(R_StickInput_.x) > 0.2f) {

		// 入力に基づいて角度を更新
		cameraAngle_ = R_StickInput_.x * kAngleSpeed_;
	}

	// 回す
	//camera_.srt.rotate.y += cameraAngle_;
}

