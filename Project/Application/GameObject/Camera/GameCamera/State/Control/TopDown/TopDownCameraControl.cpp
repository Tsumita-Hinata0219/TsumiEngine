#include "TopDownCameraControl.h"
#include "../../../GameCamera.h"
#include "../../../../../Character/Player/Player.h"


/// <summary>
/// 初期化
/// </summary>
void TopDownCameraControl::Enter(GameCamera* pCamera, CameraResource* pData)
{
	pGameCamera_ = pCamera;
	pData_ = pData;

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
void TopDownCameraControl::Update() 
{
	// フォロー処理
	FuncFollow();
}


/// <summary>
/// 回転処理
/// </summary>
void TopDownCameraControl::FuncOrientation()
{
}


/// <summary>
/// フォロー処理
/// </summary>
void TopDownCameraControl::FuncFollow()
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

