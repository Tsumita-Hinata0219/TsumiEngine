#include "Player.h"



// 初期化処理
void Player::Init()
{
	// Inputクラス
	input_ = Input::GetInstance();

	// BodyModelのロードと初期化
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Player", "Player.obj");
	model_ = modelManager_->GetModel("Player");

	// BodyTransformの初期化
	trans_.Initialize();
}


// 更新処理
void Player::Update()
{
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

#ifdef _DEBUG
	if (ImGui::TreeNode("Player")) {
		trans_.DrawImGui();
		ImGui::Text("");
		ImGui::Text("ShotFrame = %d", shotPressFrame_);

		ImGui::Text("");
		light_.DrawImGui();

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
	// 射撃時はRStickのInputを取得
	if (input_->Press(DIK_SPACE) || input_->Press(PadData::RIGHT_SHOULDER)) {
		
		//Stickの入力を取得
		stickInput_ = input_->GetRStick();
	}
	else {
		//Stickの入力を取得
		stickInput_ = input_->GetLStick();
	}

	// Stick入力がいていい範囲を超えている場合、角度を更新
	// stick入力が一定範囲を超えている場合、角度を更新
	if (std::abs(stickInput_.x) > 0.2f || std::abs(stickInput_.y) > 0.2f) {

		// Y軸周り角度(θy)
		trans_.srt.rotate.y = std::atan2(stickInput_.x, stickInput_.y);
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

