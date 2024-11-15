#pragma once

#include "../ICameraControlStateh.h"


/* カメラの操作処理の
   俯瞰視点時の処理*/
class TopDownCameraControl : public ICameraControlStateh {

public:

	// コンストラクタ
	TopDownCameraControl() = default;

	// 初期化、更新
	void Enter(GameCamera* pCamera, CameraResource* pData) override;
	void Update() override;


};

