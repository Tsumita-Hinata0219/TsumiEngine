#pragma once

#include "../IPlayerMovement.h"


/* プレイヤーの周りを回るカメラの
   処理の時の移動処理 */
class OrbitalCameraMovement : public IPlayerMovement {

public:

	// コンストラクタ
	OrbitalCameraMovement() = default;

	// 初期化、更新
	void Enter(Player* pPlayer) override;
	void Update() override;

private:


};

