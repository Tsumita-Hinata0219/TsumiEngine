#pragma once

#include "GameObject/GameObject.h"
#include "Math/MyMath.h"

// GameCameraの前方宣言
class GameCamera;
struct CameraResource;
class Player;

/* IPlayerMovementの基底クラス
   移動処理のステートパターン */
class ICameraControlState {

public:

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~ICameraControlState() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Enter(GameCamera* pCamera, CameraResource* pData) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// プレイヤーのアクセッサ
	/// </summary>
	virtual void SetPlayer(Player* setPlayer) { this->pPlayer_ = setPlayer; }


protected:

	GameCamera* pGameCamera_ = nullptr;
	CameraResource* pData_;
	Player* pPlayer_ = nullptr;

};



