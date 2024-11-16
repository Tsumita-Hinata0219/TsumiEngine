#pragma once

#include "../IPlayerMovement.h"


/* プレイヤーの周りを回るカメラの
   処理の時の移動処理 */
class OrbitalCameraMovement : public IPlayerMovement {

public:

	// コンストラクタ
	OrbitalCameraMovement() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Enter(Player* pPlayer) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:


};

