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

	// 仮想デストラクタ
	virtual ~IPlayerMovement() = default;

	// 初期化、更新
	virtual void Enter(Player* pPlayer, Transform* pTrans) = 0;
	virtual void Update() = 0;

protected:

	Player* pPlayer_ = nullptr;
	GameCamera* pGameCamera_ = nullptr;
	Transform* pTrans_{};

};

