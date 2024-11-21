#pragma once
#include "GameObject/GameObject.h"
#include "Math/MyMath.h"

// 前方宣言
class GameCamera;
struct CameraResource;
class Player;

/* GameCameraの操作処理のクラス */
class GameCameraControl {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCameraControl() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameCameraControl() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(GameCamera* pCamera, Player* setPlayer, CameraResource* pData);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


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

	// 各ポインター
	GameCamera* pGameCamera_ = nullptr;
	Player* pPlayer_ = nullptr;
	CameraResource* pData_;

	// 入力
	TsumiEngine::Input* input_ = nullptr;
	// LStickの入力
	Vector2 iRStick_{};
	// デッドゾーン
	const float DZone_ = 0.2f;

	// 回転速度
	float addOrientationSpeed_ = 0.15f;
	// 姿勢計算の補間速度
	float orientationLerpSpeed_ = 0.5f;

	// 姿勢
	Vector3 initRotate_{};

	// 相対位置
	Vector3 constOffset_{};
	// プレイヤーからのオフセット
	Vector3 playerOffset_{};
};

