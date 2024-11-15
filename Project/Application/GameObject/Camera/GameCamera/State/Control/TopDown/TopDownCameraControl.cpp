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
}


/// <summary>
///	更新処理
/// </summary>
void TopDownCameraControl::Update() {}
