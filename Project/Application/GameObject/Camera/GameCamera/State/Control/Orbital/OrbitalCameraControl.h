#pragma once

#include "../ICameraControlState.h"


/* カメラの操作処理の
   フォローカメラ時の処理*/
class OrbitalCameraControl : public ICameraControlState {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	OrbitalCameraControl() = default;

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

	// 入力
	Input* input_ = nullptr;
	// LStickの入力
	Vector2 iRStick_{};
	// デッドゾーン
	const float DZone_ = 0.2f;

	// 回転速度
	float addOrientationSpeed_ = 0.15f;
	// 姿勢計算の補間速度
	float orientationLerpSpeed_ = 0.5f;

	// 相対位置
	Vector3 constOffset_{};
	// プレイヤーからのオフセット
	Vector3 playerOffset_{};

};

