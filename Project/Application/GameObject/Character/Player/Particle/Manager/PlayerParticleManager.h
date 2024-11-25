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


#pragma region Accessor アクセッサ

	// Playerのポインタ
	void SetPlayer(Player* setPlayer) { this->player_ = setPlayer; }

#pragma endregion 


private:

	/// <summary>
	/// 移動パーティクルの追加
	/// </summary>
	void AddMovementPartiucle();

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();


private:

	// Player
	Player* player_ = nullptr;

	// MovementParticle
	//std::list<std::shared_ptr<PlayerMovementParticle>> movementParticles_;
	std::list<std::shared_ptr<IPlayerParticle>> particleList_;;

};

