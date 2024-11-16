#pragma once

#include "../IPlayerMovement.h"


/* 俯瞰視点のカメラの
   処理の時の移動処理 */
class TopDownCameraMovement : public IPlayerMovement {

public:

	// コンストラクタ
	TopDownCameraMovement() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Enter(Player* pPlayer, Transform* pTrans) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:


};

