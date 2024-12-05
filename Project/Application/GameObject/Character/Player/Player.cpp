#include "Player.h"
#include "../../Camera/FollowCamera/FollowCamera.h"
#include "../../Camera/GameCamera/GameCamera.h"


/// <summary>
/// 初期化処理
/// </summary>
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

	// 各ボディの初期化とペアレントを結ぶ
	iBodys_.resize(EnumSize<PlayerBodyTyep>::value);
	iBodys_[enum_val(PlayerBodyTyep::MAIN)] = std::make_unique<PlayerMainBody>();
	iBodys_[enum_val(PlayerBodyTyep::LEFT)] = std::make_unique<PlayerLeftBody>();
	iBodys_[enum_val(PlayerBodyTyep::RIGHTM)] = std::make_unique<PlayerRightBody>();
	for (std::shared_ptr<IPlayerBody> body : iBodys_) {
		body->Init();
		body->SetParent(&trans_);
	}

	// ライトの初期設定
	light_.enable = true;
	light_.direction = Vector3::oneY;
	light_.intensity = 0.7f;

	//Transformの初期化
	trans_.Init();
	trans_.srt.translate.z = -5.0f;

	// パーティクルマネージャー
	particleManager_ = std::make_unique<PlayerParticleManager>();
	particleManager_->Init();
	particleManager_->SetPlayer(this);

	// 移動処理クラス
	movement_ = std::make_unique<PlayerMovement>();
	movement_->Init(this, gameCamera_, &trans_);

	// BulletのObjectPoolを先に作っておく
	bulletPool_.Create(50);

	// Colliderの初期化
	sphere_ = std::make_unique<SphereCollider>(this);
	sphere_->data_.center = trans_.GetWorldPos();
	sphere_->data_.radius = 2.0f;


	// キルカウントを0で初期化
	killCount_ =0;

	// HPの設定
	hp_ = 3;

	// 無敵状態の時間を設定しておく
	invincibilityTime_ = invincibilityInterval_;
}


/// <summary>
///  更新処理
/// </summary>
void Player::Update()
{
	// UI
	ui_->Update();

	// Transformの更新処理
	trans_.UpdateMatrix();

	// パーティクルマネージャー
	particleManager_->Update();

	// プレイヤーの操作関連
	movement_->Update();

	// 射撃の処理
	ExecuteShot();

	// Bulletの更新処理
	for (PlayerBullet* bullet : bulletList_) {
		bullet->Update();
	}
	// 死亡フラグが立っていたら削除
	bulletList_.remove_if([this](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			// 返却する前にリセット処理を入れておく
			bullet->Reset();
			// 死亡したバレットをプールに返却
			bulletPool_.Return(bullet);
			return true;
		}
		return false;
		}
	);

	// ColliderのSRTの設定
	sphere_->data_.center = trans_.GetWorldPos();


	// キルカウントが一定を超えていたら勝利フラグを立てる
	if (killCount_ >= MaxKillCount_) {
		isWin_ = true;
		isLose_ = false;
	}
	// 体力が0なら敗北フラグを立てる
	if (hp_ <= HP_MIN) {
		isWin_ = false;
		isLose_ = true;
	}

	// 無敵状態のタイマーを減らす処理
	if (isInvincibility_) {
		SubtructInvincibilityTime();
	}

	if (input_->Trigger(DIK_RETURN)) {
		isWin_ = true;
	}


#ifdef _DEBUG
	// ImGuiの描画
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void Player::Draw3D()
{
	// BodyModelの描画
	for (std::shared_ptr<IPlayerBody> body : iBodys_) {
		body->SetModelColor(color_);
		body->SetModelLight(light_);
		body->Draw3D();
	}

	// ParticleManagerの描画
	particleManager_->Draw();

	// Bulletsの描画
	for (PlayerBullet* bullet : bulletList_) {
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


/// <summary>
/// 衝突判定コールバック関数
/// </summary>
void Player::onCollision([[maybe_unused]] IObject* object)
{
	if (object->GetCategory() == Attributes::Category::TERRAIN) {

		//// 押し出しの処理
		//trans_.UpdateMatrix();
		//colComp_->Penetration(&trans_.srt.translate, sphere_);
		//trans_.UpdateMatrix();
	}
	if (object->GetCategory() == Attributes::Category::ENEMY && 
		object->GetType() == Attributes::Type::BULLET) {

		//OnCollisionWithEnemyBullet();
	}
}
void Player::OnCollisionWithEnemy()
{


}
void Player::OnCollisionWithEnemyBullet()
{
	// 早期return
	if (isInvincibility_) return; // 無敵時間
	if (hp_ <= HP_MIN) return; // 体力が0以下

	// 無敵時間にする
	isInvincibility_ = true;

	// HP減少
	if (hp_ > HP_MIN) {
		hp_--;
	}

	// 体力がなければ消すモデルもないので通らない
	if (hp_ >= HP_MIN) {

		// 体力減少具合でボディを減らす
		iBodys_[hp_].reset();

		// nullになった要素を削除
		iBodys_.erase(std::remove_if(iBodys_.begin(), iBodys_.end(), [](const std::shared_ptr<IPlayerBody>& body) {
			return body == nullptr;
			}
		),
			iBodys_.end()
		);

		// ボディモデルのカラーを赤にする
		for (auto& body : this->iBodys_) {
			body->SetModelColor(Samp::Color::RED);
		}
	}
}


/// <summary>
/// 入力を受け取る
/// </summary>
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


/// <summary>
/// プレイヤーの移動
/// </summary>
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


/// <summary>
/// 移動方向を求める
/// </summary>
void Player::CalcMoveDirection()
{
	// カメラの前方と右方
	Vector3 forward = gameCamera_->GetForwardVec();
	Vector3 right = gameCamera_->GetRightVec();

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


/// <summary>
/// 移動処理
/// </summary>
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


/// <summary>
/// 移動限界処理
/// </summary>
void Player::MoveLimited()
{
	// 移動限界
	const float kMoveMit = 100.0f;
	trans_.srt.translate.x = max(trans_.srt.translate.x, -kMoveMit);
	trans_.srt.translate.x = min(trans_.srt.translate.x, +kMoveMit);
	trans_.srt.translate.z = max(trans_.srt.translate.z, -kMoveMit);
	trans_.srt.translate.z = min(trans_.srt.translate.z, +kMoveMit);
}


/// <summary>
/// カメラの方向に体の向きを合わせる
/// </summary>
void Player::FaceCameraDirection()
{
	// カメラの前方ベクトルを取得
	Vector3 cameraForward = gameCamera_->GetForwardVec();

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


/// <summary>
/// 移動方向からY軸の姿勢を合わせる
/// </summary>
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


/// <summary>
/// 射撃処理
/// </summary>
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
		
		shotPressFrame_ = kInitialShotPressFrame;

		// フラグを折る
		isShooting_ = false;
	}
}


/// <summary>
/// 新しいバレットを生成する
/// </summary>
void Player::CreateNewBullet()
{
	// オブジェクトプール空新しいバレットを取得
	PlayerBullet* newBullet = bulletPool_.Get();

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


/// <summary>
/// 無敵状態のタイマーを減らす処理
/// </summary>
void Player::SubtructInvincibilityTime()
{
	// 定数定義
	constexpr int kColorResetThreshold = 7; // モデルカラーをリセットするまでのフレーム数

	// 無敵状態の時間を減らす
	invincibilityTime_--;

	// 一定フレームたったら
	if (invincibilityTime_ == invincibilityInterval_ - kColorResetThreshold) {

		// モデルのカラーを白に戻す
		for (auto& body : this->iBodys_) {
			body->SetModelColor(Samp::Color::WHITE);
		}
	}

	if (invincibilityTime_ <= invincibilityResetTime_) {
		// 状態解除
		isInvincibility_ = false;
		// タイマーリセット
		invincibilityTime_ = invincibilityInterval_;
	}
}


/// <summary>
/// ImGuiの描画
/// </summary>
void Player::DrawImGui()
{
	if (ImGui::TreeNode("Player")) {

		ImGui::Text("Transform");
		trans_.DrawImGui();
		ImGui::Text("");

		ImGui::Text("BodyColor");
		ImGui::ColorEdit4("color", &color_.x);
		ImGui::Text("");

		ImGui::Text("BodyLight");
		light_.DrawImGui();
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

		ImGui::Text("Bullet");
		int instance = int(bulletList_.size());
		ImGui::DragInt("Bullet_InstanceSize", &instance, 0);

		ImGui::Text("Invincibility");
		ImGui::Checkbox("Invincibility", &isInvincibility_);
		ImGui::Text("InvincibilityTime = %d", invincibilityTime_);
		ImGui::Text("");

		ImGui::Text("Movement");
		ImGui::Checkbox("isMovement", &movement_->IsMovement());
		ImGui::Text("");

		ImGui::TreePop();
	}
}

