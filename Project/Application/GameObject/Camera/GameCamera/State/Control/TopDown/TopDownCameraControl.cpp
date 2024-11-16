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
	orientatin_ = Vector3::one;

	// 相対位置
	constOffset_ = Vector3::one;

	// カメラ姿勢のデータに設定
	pData_->srt.rotate = orientatin_;

}


/// <summary>
///	更新処理
/// </summary>
void TopDownCameraControl::Update() 
{
	pData_->srt.translate =
		pPlayer_->GetWorldPos() + constOffset_;

}

