#include "OrbitalCameraMovement.h"
#include "../../../Player.h"
#include "GameObject/Camera/GameCamera/GameCamera.h"


/// <summary>
/// 初期化処理
/// </summary>
void OrbitalCameraMovement::Enter(Player* pPlayer, Transform* pTrans)
{
	pPlayer_ = pPlayer;
	pTrans_ = pTrans;

	// Inputクラス
	input_ = Input::GetInstance();
}


/// <summary>
/// 更新処理
/// </summary>
void OrbitalCameraMovement::Update()
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


	// Velocityは0で初期化しておく
	velocity_ = Vector3::zero;

	// 移動処理
	PadMove();
	KeyMove();

	if (pPlayer_->IsShooting()) {
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
void OrbitalCameraMovement::CalcMoveDirection()
{
	// カメラの前方と右方
	Vector3 forward = pGameCamera_->GetForwardVec();
	Vector3 right = pGameCamera_->GetRightVec();

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
void OrbitalCameraMovement::PadMove()
{
	// 移動量の計算
	if (std::abs(iLStick_.x) > DZone_ || std::abs(iLStick_.y) > DZone_) {

		// 移動量の計算(カメラの前方と右方に基づく)
		velocity_ = stickMoveDirection_;

		// 移動方向を正規化し速さを乗算
		velocity_ = Normalize(velocity_) * moveSpeed_;

		// 座標に加算
		pTrans_->srt.translate += velocity_;
	}
}
void OrbitalCameraMovement::KeyMove()
{
	// 移動量の計算
	if (std::abs(iKeys_.x) > DZone_ || std::abs(iKeys_.y) > DZone_) {

		// 移動量の計算(カメラの前方と右方に基づく)
		velocity_ = keyMoveDirection_;

		// 移動方向を正規化し速さを乗算
		velocity_ = Normalize(velocity_) * moveSpeed_;

		// 座標に加算
		pTrans_->srt.translate += velocity_;
	}
}


/// <summary>
/// カメラの方向に体の向きを合わせる
/// </summary>
void OrbitalCameraMovement::FaceCameraDirection()
{
	// カメラの前方ベクトルを取得
	Vector3 cameraForward = pGameCamera_->GetForwardVec();

	// カメラのY成分を無視して水平面上の方向を計算
	cameraForward.y = 0.0f;
	cameraForward = Normalize(cameraForward);  // 正規化して方向ベクトルにする

	// 目標の回転角度を求める（Y軸の回転）
	float targetAngle = std::atan2(cameraForward.x, cameraForward.z);

	// 現在の角度と目標角度から最短を求める
	float shortestAngle = ShortestAngle(pTrans_->srt.rotate.y, targetAngle);

	// 現在の角度を目標角度の間を補間
	pTrans_->srt.rotate.y =
		Lerp(pTrans_->srt.rotate.y, pTrans_->srt.rotate.y + shortestAngle, orientationLerpSpeed_);
}


/// <summary>
/// 移動方向からY軸の姿勢を合わせる
/// </summary>
void OrbitalCameraMovement::CalcBodyOrienation(Vector2 input, Vector3 direction)
{
	if (std::abs(input.x) > DZone_ || std::abs(input.y) > DZone_)
	{
		// 正規化した移動方向
		Vector3 normalizeDirection = Normalize(direction);

		// 目標回転角度
		float targetAngle = std::atan2(normalizeDirection.x, normalizeDirection.z);

		// 現在の角度と目標角度から最短を求める
		float shortestAngle = ShortestAngle(pTrans_->srt.rotate.y, targetAngle);

		// 現在の角度を目標角度の間を補間
		pTrans_->srt.rotate.y =
			Lerp(pTrans_->srt.rotate.y, pTrans_->srt.rotate.y + shortestAngle, orientationLerpSpeed_);
	}
}

