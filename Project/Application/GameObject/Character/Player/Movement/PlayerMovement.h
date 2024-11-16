#pragma once

#include "Math/MyMath.h"
#include "GameObject/GameObject.h"


// 前方宣言
class Player;
class GameCamera;
struct Transform;

/* プレイヤーの移動処理をするクラス */
class PlayerMovement {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerMovement() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerMovement() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Player* pPlayer, GameCamera* pGameCamera, Transform* pTrans);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


private:

	/// <summary>
	/// 移動方向を求める
	/// </summary>
	void CalcMoveDirection();

	/// <summary>
	/// 移動処理
	/// </summary>
	void PadMove();
	void KeyMove();

	/// <summary>
	/// カメラの方向に体の向きを合わせる
	/// </summary>
	void FaceCameraDirection();

	/// <summary>
	/// 移動方向からY軸の姿勢を合わせる
	/// </summary>
	void CalcBodyOrienation(Vector2 input, Vector3 direction);


private:

	// 各ポインター
	Player* pPlayer_ = nullptr;
	GameCamera* pGameCamera_ = nullptr;
	Transform* pTrans_{};


	// 移動方向
	Vector3 stickMoveDirection_{};
	Vector3 keyMoveDirection_{};
	// 移動量
	Vector3 velocity_{};
	// 移動速度
	float moveSpeed_ = 0.2f;

	// 姿勢計算の補間速度
	float orientationLerpSpeed_ = 0.1f;

	// Inputクラス
	Input* input_ = nullptr;

	// デッドゾーン
	const float DZone_ = 0.2f;

	//Stickの入力を取得
	Vector2 iLStick_{};
	Vector2 iRStick_{};
	// Keyの入力
	Vector2 iKeys_{};

};

