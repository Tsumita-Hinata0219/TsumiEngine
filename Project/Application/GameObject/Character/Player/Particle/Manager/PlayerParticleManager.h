#pragma once

#include "../Interface/IPlayerParticle.h"
#include "../Movement/PlayerMovementParticle.h"


// 前方宣言
class Player;


/* プレイヤー関連のパーティクルマネージャー */
class PlayerParticleManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerParticleManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerParticleManager() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


private:

	// Player
	Player* player = nullptr;

	// MovementParticle
	std::list<PlayerMovementParticle> movementParticles_;

};

