#include "OrbitalCameraControl.h"
#include "../../../GameCamera.h"
#include "../../../../../Character/Player/Player.h"


/// <summary>
/// 初期化
/// </summary>
void OrbitalCameraControl::Enter(GameCamera* pCamera, CameraResource* pData)
{
	pGameCamera_ = pCamera;
	pData_ = pData;

	// Inputクラス
	input_ = Input::GetInstance();

	// 姿勢
	initRotate_ = { 0.3f, 0.0f, 0.0f };
	pData_->srt.rotate = initRotate_;

	// 相対位置
	constOffset_ = { 0.0f, 20.0f, -50.0f };

	// オフセットの設定
	playerOffset_ = constOffset_;
}


/// <summary>
///	更新処理
/// </summary>
void OrbitalCameraControl::Update()
{
	// stickの入力を受け取る
	iRStick_ = input_->GetRStick();

	// 回転処理
	FuncOrientation();

	// フォロー処理
	FuncFollow();
}


/// <summary>
/// 回転処理
/// </summary>
void OrbitalCameraControl::FuncOrientation()
{
	if (std::abs(iRStick_.x) > DZone_ || std::abs(iRStick_.y) > DZone_) {

		// 目標回転角度
		float addAngle = iRStick_.x * addOrientationSpeed_;

		// 現在の角度と目標角度の計算
		float targetAngle = pData_->srt.rotate.y + addAngle;

		// 現在の角度を目標角度の間を補間
		pData_->srt.rotate.y =
			Lerp(pData_->srt.rotate.y, targetAngle, orientationLerpSpeed_);
	}
}


/// <summary>
/// フォロー処理
/// </summary>
void OrbitalCameraControl::FuncFollow()
{
	// オフセットの設定
	playerOffset_ = constOffset_;

	// カメラの前方方向に基づいてカメラのオフセットを回転させる
	Matrix4x4 rotateMat = Matrix4x4::identity;
	rotateMat = MakeRotateYMatrix(pData_->srt.rotate.y);

	// カメラのオフセットの回転
	playerOffset_ = TransformWithPerspective(playerOffset_, rotateMat);

	// プレイヤーの位置にオフセットを加えてカメラの位置を更新
	pData_->srt.translate = pPlayer_->GetWorldPos() + playerOffset_;

	// Yの位置だけ固定
	pData_->srt.translate.y = constOffset_.y;
}

