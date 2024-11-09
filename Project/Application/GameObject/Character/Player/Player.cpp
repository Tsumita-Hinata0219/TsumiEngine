#include "Player.h"
#include "../../Camera/FollowCamera/FollowCamera.h"


// 初期化処理
void Player::Init()
{
	// Inputクラス
	input_ = Input::GetInstance();

	// UI
	ui_ = std::make_unique<PlayerUI>();
	ui_->Init();

	// BodyModelのロード
	modelManager_->LoadModel("Obj/Player/Body/Main", "Player_Main_Body.obj");
	modelManager_->LoadModel("Obj/Player/Body/Center", "Player_Center_Body.obj");
	modelManager_->LoadModel("Obj/Player/Body/Left", "Player_Left_Body.obj");
	modelManager_->LoadModel("Obj/Player/Body/Right", "Player_Right_Body.obj");
	// BulletModelのロード
	modelManager_->LoadModel("Obj/Player/Bullet", "PlayerBullet.obj");

	//Transformの初期化
	trans_.Init();

	// 各ボディの初期化とペアレントを結ぶ
	iBodys_.resize(EnumSize<PlayerBodyTyep>::value);
	iBodys_[enum_val(PlayerBodyTyep::MAIN)] = std::make_unique<PlayerMainBody>();
	iBodys_[enum_val(PlayerBodyTyep::LEFT)] = std::make_unique<PlayerLeftBody>();
	iBodys_[enum_val(PlayerBodyTyep::RIGHTM)] = std::make_unique<PlayerRightBody>();
	for (std::shared_ptr<IPlayerBody> body : iBodys_) {
		body->Init();
		body->SetParent(&trans_);
	}

	// Colliderの登録
	colComp_->SetAttribute(ColliderAttribute::Player);
	colComp_->Register(sphere_);
	sphere_.center = trans_.GetWorldPos();
	sphere_.radius = 2.0f;

	// キルカウントを0で初期化
	killCount_ = 0;

	// HPの設定
	hp_ = 3;
}


// 更新処理
void Player::Update()
{
	// UI
	ui_->Update();

	// Transformの更新処理
	trans_.UpdateMatrix();

	// 入力を受け取る
	InputFunc();

	// プレイヤーの操作関連
	MoveFunc();

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
	sphere_.center = trans_.GetWorldPos();

	//// キルカウントが一定を超えていたら勝利フラグを立てる
	//if (killCount_ >= 15) {
	//	isWin_ = true;
	//	isLose_ = false;
	//}
	//// 体力が0なら敗北フラグを立てる
	//if (hp_ <= 0) {
	//	isWin_ = false;
	//	isLose_ = true;
	//}

#ifdef _DEBUG
	// ImGuiの描画
	DrawImGui();
#endif // _DEBUG
}


// 描画処理
void Player::Draw3D()
{
	// BodyModelの描画
	for (std::shared_ptr<IPlayerBody> body : iBodys_) {
		body->Draw3D();
	}

	// Bulletsの描画
	for (std::shared_ptr<PlayerBullet> bullet : bulletList_) {
		bullet->Draw3D();
	}
}
void Player::Draw2DBack() 
{
	// UI Back
	ui_->Draw2DBack();
}
void Player::Draw2DFront() 
{
	// UI Front
	ui_->Draw2DFront();
}


// 衝突自コールバック関数
void Player::onCollision([[maybe_unused]] IObject* object)
{
}
void Player::OnCollisionWithEnemy()
{


}
void Player::OnCollisionWithEnemyBullet()
{
	// HP減少
	//hp_--;

	// 体力がなければ消すモデルもないので通らない
	if (hp_ >= 0) {

		// 体力減少具合でボディを減らす
		iBodys_[hp_].reset();

		// nullになった要素を削除
		iBodys_.erase(std::remove_if(iBodys_.begin(), iBodys_.end(), [](const std::shared_ptr<IPlayerBody>& body) {
			return body == nullptr;
			}
		),
			iBodys_.end()
		);
	}
}


// 入力を受け取る
void Player::InputFunc()
{
	// stickの入力を取得
	iLStick_ = input_->GetLStick();

	// keyの入力を取得
	iKeys_ = Vector2::zero;
	if (input_->Press(DIK_W)) {
		iKeys_.y = 1.0f;
	}
	if (input_->Press(DIK_S)) {
		iKeys_.y = -1.0f;
	}
	if (input_->Press(DIK_A)) {
		iKeys_.x = -1.0f;
	}
	if (input_->Press(DIK_D)) {
		iKeys_.x = 1.0f;
	}
}


// プレイヤーの移動
void Player::MoveFunc()
{
	// 移動方向を求める
	CalcMoveDirection();

	// Velocityは0で初期化しておく
	velocity_ = Vector3::zero;

	// 移動処理
	PadMove();
	KeyMove();

	// 移動限界処理
	MoveLimited();

	if (isShooting_) {
		// 射撃中はカメラの進行方向に姿勢を合わせる
		FaceCameraDirection();
	}
	else {
		// 移動方向からY軸の姿勢を合わせる
		CalcBodyOrienation(iLStick_, stickMoveDirection_);
		CalcBodyOrienation(iKeys_, keyMoveDirection_);
	}
}


// 移動方向を求める
void Player::CalcMoveDirection()
{
	// カメラの前方と右方
	Vector3 forward = followCamera_->GetForwardVec();
	Vector3 right = followCamera_->GetRightVec();

	stickMoveDirection_ = {
		(iLStick_.x * right.x) + (iLStick_.y * forward.x),
		0.0f,
		(iLStick_.x * right.z) + (iLStick_.y * forward.z),
	};
	keyMoveDirection_ = {
		(iKeys_.x * right.x) + (iKeys_.y * forward.x),
		0.0f,
		(iKeys_.x * right.z) + (iKeys_.y * forward.z),
	};
}


// 移動処理
void Player::PadMove()
{
	// 移動量の計算
	if (std::abs(iLStick_.x) > DZone_ || std::abs(iLStick_.y) > DZone_) {

		// 移動量の計算(カメラの前方と右方に基づく)
		velocity_ = stickMoveDirection_;

		// 移動方向を正規化し速さを乗算
		velocity_ = Normalize(velocity_) * moveSpeed_;

		// 座標に加算
		trans_.srt.translate += velocity_;
	}
}
void Player::KeyMove()
{
	// 移動量の計算
	if (std::abs(iKeys_.x) > DZone_ || std::abs(iKeys_.y) > DZone_) {

		// 移動量の計算(カメラの前方と右方に基づく)
		velocity_ = keyMoveDirection_;

		// 移動方向を正規化し速さを乗算
		velocity_ = Normalize(velocity_) * moveSpeed_;

		// 座標に加算
		trans_.srt.translate += velocity_;
	}
}


// 移動限界処理
void Player::MoveLimited()
{
}


// カメラの方向に体の向きを合わせる
void Player::FaceCameraDirection()
{
	// カメラの前方ベクトルを取得
	Vector3 cameraForward = followCamera_->GetForwardVec();

	// カメラのY成分を無視して水平面上の方向を計算
	cameraForward.y = 0.0f;
	cameraForward = Normalize(cameraForward);  // 正規化して方向ベクトルにする

	// 目標の回転角度を求める（Y軸の回転）
	float targetAngle = std::atan2(cameraForward.x, cameraForward.z);

	// 現在の角度と目標角度から最短を求める
	float shortestAngle = ShortestAngle(trans_.srt.rotate.y, targetAngle);

	// 現在の角度を目標角度の間を補間
	trans_.srt.rotate.y =
		Lerp(trans_.srt.rotate.y, trans_.srt.rotate.y + shortestAngle, orientationLerpSpeed_);
}


// 移動方向からY軸の姿勢を合わせる
void Player::CalcBodyOrienation(Vector2 input, Vector3 direction)
{
	if (std::abs(input.x) > DZone_ || std::abs(input.y) > DZone_)
	{
		// 正規化した移動方向
		Vector3 normalizeDirection = Normalize(direction);

		// 目標回転角度
		float targetAngle = std::atan2(normalizeDirection.x, normalizeDirection.z);

		// 現在の角度と目標角度から最短を求める
		float shortestAngle = ShortestAngle(trans_.srt.rotate.y, targetAngle);

		// 現在の角度を目標角度の間を補間
		trans_.srt.rotate.y = 
			Lerp(trans_.srt.rotate.y, trans_.srt.rotate.y + shortestAngle, orientationLerpSpeed_);
	}
}


// 射撃処理
void Player::ExecuteShot()
{
	// キーorボタン押下でタイマーをデクリメント
	if (input_->Press(DIK_SPACE) || input_->Press(PadData::RIGHT_SHOULDER)) {

		shotPressFrame_--;

		// 射撃中のフラグを立てる
		isShooting_ = true;

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

		// フラグを折る
		isShooting_ = false;
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
	newBullet->SetPlayer(this);

	// リストに追加
	bulletList_.push_back(newBullet);
}


// ImGuiの描画
void Player::DrawImGui()
{
	if (ImGui::TreeNode("Player")) {

		ImGui::Text("Transform");
		trans_.DrawImGui();
		ImGui::Text("");

		ImGui::Text("Move");
		ImGui::DragFloat3("Velocity", &velocity_.x, 0.0f);
		ImGui::Text("");

		ImGui::Text("KillCount = %d", killCount_);
		ImGui::Text("");

		ImGui::Text("HP = %d", hp_);
		ImGui::Text("");

		//ImGui::Text("入力関連");
		ImGui::Text("Input");
		ImGui::DragFloat2("L_Stick", &iLStick_.x, 0.0f);
		ImGui::Text("");

		ImGui::Text("Shoot");
		ImGui::Checkbox("isShooting", &isShooting_);
		ImGui::Text("");

		ImGui::TreePop();
	}
}

