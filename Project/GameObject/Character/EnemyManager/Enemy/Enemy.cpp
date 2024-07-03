#include "Enemy.h"
#include "../../Player/Player.h"


// 初期化処理
void Enemy::Initialize()
{
	// BodyModelのロードと初期化
	bodyModel_ = make_unique<Model>();
	bodyModel_->CreateFromObjAssimpVer("Test", "Test");

	// BodyTransformの初期化
	bodyWt_.Initialize();
	bodyWt_.srt.translate.z = 20.0f;
}


// 更新処理
void Enemy::Update()
{
	// Transformの更新処理
	bodyWt_.UpdateMatrix();

	// 戦闘状態の切り替え処理
	ToggleCombatState();

	// 戦闘状態に入っていたら入る処理
	if (isCombatActive_) {

		// 移動処理
		Move();

		// 射撃の処理
		ExecuteShot();
	}



#ifdef _DEBUG

	if (ImGui::TreeNode("Enemy")) {

		ImGui::Text("Transform");
		ImGui::DragFloat3("Scale", &bodyWt_.srt.scale.x, 0.01f, 0.0f, 20.0f);
		ImGui::DragFloat3("Rotate", &bodyWt_.srt.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &bodyWt_.srt.translate.x, 0.01f);

		ImGui::Text("");
		ImGui::Checkbox("CombatActive", &isCombatActive_);

		ImGui::Text("");
		ImGui::Text("ShotFrame = %d : Interval = %d", shotFrame_, kShotInterval_);

		ImGui::TreePop();
	}


#endif // _DEBUG
}


// 描画処理
void Enemy::Draw3D(Camera* camera)
{
	// BodyModelの描画
	bodyModel_->Draw(bodyWt_, camera);
}


// 戦闘状態の切り替え処理
void Enemy::ToggleCombatState()
{
	// プレイヤーとの距離で戦闘状態のフラグを管理する
	// 設定した距離よりも近くにいたらフラグを立てる
	if (std::abs(Length(player_->GetPosition() - bodyWt_.GetWorldPos())) <= combatTriggerDistance_) {

		// 戦闘状態のフラグを立てる
		isCombatActive_ = true;
	}
	else {

		// 戦闘状態のフラグを折る
		isCombatActive_ = false;

		// 射撃までのフレームを設定
		shotFrame_ = kShotInterval_;
	}
}


// 移動処理
void Enemy::Move()
{
	// ある程度近ければ早期return
	if (std::abs(Length(player_->GetPosition() - bodyWt_.GetWorldPos())) <= minToPlayer_) {
		return;
	}

	// velocityを計算
	CalcVelocity();

	// 姿勢の計算
	CalcRotate();

	// 座標にvelocityを加算
	bodyWt_.srt.translate += velocity_;
}


// Velocityの計算処理
void Enemy::CalcVelocity()
{
	// 差分をNormalize
	Vector3 player2Enemy =
		Normalize(player_->GetPosition() - bodyWt_.GetWorldPos());

	// 差分Normalizeに速度をかけてvelocityに設定
	velocity_ = {
		player2Enemy.x * moveVector_,
		player2Enemy.y, // y軸は移動してほしくないのでそのまま
		player2Enemy.z * moveVector_,
	};
}


// 向きの計算処理
void Enemy::CalcRotate()
{
	// Y軸周り角度(θy)
	bodyWt_.srt.rotate.y = std::atan2(velocity_.x, velocity_.z);

	float velZ = std::sqrt((velocity_.x * velocity_.x) + (velocity_.z * velocity_.z));
	float height = -velocity_.y;

	// X軸周り角度(θx)
	bodyWt_.srt.rotate.x = std::atan2(height, velZ);
}


// 射撃の処理
void Enemy::ExecuteShot()
{
	// タイマーをデクリメント
	shotFrame_--;

	// 0以下になったら射撃&タイマーリセット
	if (shotFrame_ <= 0) {

		// バレット生成
		CreateNewBullet();

		// タイマー再設定
		shotFrame_ = kShotInterval_;
	}
}


// 新しいバレットを生成する
void Enemy::CreateNewBullet()
{



}

