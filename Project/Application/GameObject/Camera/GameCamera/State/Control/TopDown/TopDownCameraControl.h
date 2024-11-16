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


private:

	/// <summary>
	/// 回転処理
	/// </summary>
	void FuncOrientation();

	/// <summary>
	/// フォロー処理
	/// </summary>
	void FuncFollow();


private:

	// 姿勢
	Vector3 initRotate_{};

	// 相対位置
	Vector3 constOffset_{};
	// プレイヤーからのオフセット
	Vector3 playerOffset_{};

};

