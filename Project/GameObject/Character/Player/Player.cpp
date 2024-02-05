#include "Player.h"
#include "GameManager.h"


// 初期化処理
void Player::Initialize(Vector3 initTranslate)
{
	// モデルの初期化
	model_ = make_unique<Model>();
	model_->CreateFromObj("Player");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translate = initTranslate;
	worldTransform_.UpdateMatrix();

	// 加算速度
	velocity_ = Vector3::zero;

	// 移動量
	move_ = Vector3::zero;
	moveSpeed_ = 0.5f;

	// サイズ
	this->size_ = 2.0f * worldTransform_.scale;

	// コライダー
	OBBCollider::SetID(ObjectBit::Player);
	OBBCollider::SetCollosionAttribute(ObjectFileter::Player);
	OBBCollider::SetCollisionMask(ObjectFileter::Player);

	// バレットモデルの初期化
	modelBullet_ = make_unique<Model>();
	modelBullet_->CreateFromObj("PlayerBullet");

	// レティクルの初期化
	reticle_ = make_unique<PlayerReticle>();
	reticle_->SetPlayer(this);
	reticle_->Initialize((*model_), { 0.0f, 0.0f, 0.0f });
	reticle_->SetParent(&worldTransform_);
}


// 更新処理
void Player::Update(ViewProjection view)
{
	// ワールド座標の更新
	worldTransform_.UpdateMatrix();

	// OBBの設定
	SettingOBBProperties();

	// 移動処理
	Move();

	// 射撃処理
	Attack();

	// レティクルの更新処理
	ReticleUpdate(view);


#ifdef _DEBUG

	if (ImGui::TreeNode("Player")) 
	{
		ImGui::DragFloat3("Rotate", &worldTransform_.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &worldTransform_.translate.x, 0.01f);
		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void Player::Draw3D(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
	reticle_->Draw3D(view);
}
void Player::Draw2DFront(ViewProjection view)
{
	reticle_->Draw2D(view);
}


// 衝突時コールバック関数
void Player::OnCollision(uint32_t id)
{
	if (id == ObjectBit::EnemyBullet) {
		Log("isHit Player x EnemyBullet!!");
	}

}


// 移動処理
void Player::Move() {

	// 見えない壁。移動処理限界
	//worldTransform_.translate.y = min(worldTransform_.translate.y, vhInfo.up);
	//worldTransform_.translate.y = max(worldTransform_.translate.y, vhInfo.down);
	//worldTransform_.translate.x = min(worldTransform_.translate.x, vhInfo.left);
	//worldTransform_.translate.x = max(worldTransform_.translate.x, vhInfo.right);

	// move_は毎フレーム０代入
	// move_を増やすことで移動
	move_ = Vector3::zero;
	velocity_ = Vector3::zero;

	if (KeysInput::PressKeys(DIK_W)) {
		move_.y = moveSpeed_;
	}
	if (KeysInput::PressKeys(DIK_A)) {
		move_.x = -moveSpeed_;
	}
	if (KeysInput::PressKeys(DIK_S)) {
		move_.y = -moveSpeed_;
	}
	if (KeysInput::PressKeys(DIK_D)) {
		move_.x = moveSpeed_;
	}

	if (GamePadInput::PressButton(XINPUT_GAMEPAD_DPAD_UP)) {
		move_.y = moveSpeed_;
	}
	if (GamePadInput::PressButton(XINPUT_GAMEPAD_DPAD_LEFT)) {
		move_.x = -moveSpeed_;
	}
	if (GamePadInput::PressButton(XINPUT_GAMEPAD_DPAD_DOWN)) {
		move_.y = -moveSpeed_;
	}
	if (GamePadInput::PressButton(XINPUT_GAMEPAD_DPAD_RIGHT)) {
		move_.x = moveSpeed_;
	}

	// 速度を常に加算
	velocity_ = move_;
	worldTransform_.translate += velocity_;
}


// 射撃処理
void Player::Attack() {

	if (KeysInput::TriggerKey(DIK_SPACE)) {
		PushBackBulletList();
	}
	if (GamePadInput::TriggerButton(XINPUT_GAMEPAD_A)) {
		PushBackBulletList();
	}
}


// OBBの設定
void Player::SettingOBBProperties()
{
	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(this->worldTransform_.rotate);
}


// バレットリストの登録
void Player::PushBackBulletList()
{
	PlayerBullet* newBullet = new PlayerBullet();
	Vector3 newPos = worldTransform_.GetWorldPos();
	Vector3 newVel = CalcDirection();

	newBullet->Initialize((*modelBullet_), newPos, newVel);

	GameScene_->AddPlayerBulletList(newBullet);
}


// バレットの進行方向の計算
Vector3 Player::CalcDirection()
{
	Vector3 ReticlePos = reticle_->GetWorldPosition();
	Vector3 PlaToRet = Normalize(ReticlePos - worldTransform_.GetWorldPos());
	return PlaToRet * kBulletSpeed_;
}


// レティクルの更新処理
void Player::ReticleUpdate(ViewProjection view)
{
	reticle_->Update(view);
}

