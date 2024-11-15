#pragma once

#include "../ICameraControlState.h"


/* カメラの操作処理の
   俯瞰視点時の処理*/
class TopDownCameraControl : public ICameraControlState {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TopDownCameraControl() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Enter(GameCamera* pCamera, CameraResource* pData) override;

	/// <summary>
	///	更新処理
	/// </summary>
	void Update() override;


};

