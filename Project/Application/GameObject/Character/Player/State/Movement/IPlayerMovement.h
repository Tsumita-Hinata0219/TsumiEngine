#pragma once

#include "Math/MyMath.h"
#include "GameObject/GameObject.h"


// Playerの前方宣言
class Player;
class GameCamera;
struct Transform;

/* IPlayerMovementの基底クラス
   移動処理のステートパターン */
class IPlayerMovement {

public:

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IPlayerMovement() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Enter(Player* pPlayer, Transform* pTrans) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// カメラの設定
	/// </summary>
	void SetCamera(GameCamera* setCamera) { this->pGameCamera_ = setCamera; }


protected:

	Player* pPlayer_ = nullptr;
	GameCamera* pGameCamera_ = nullptr;
	Transform* pTrans_{};

};

