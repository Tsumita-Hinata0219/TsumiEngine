#pragma once

#include "GameObject.h"


// Playerの前方宣言
class Player;

/* PlayerReticleクラス */
class PlayerReticle {

public: // メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model& modelHD, Vector3 initTranslate);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

#pragma region Set

	/// <summary>
	/// Playerの設定
	/// </summary>
	void SetPlayer(Player* player) { this->player_ = player; }

#pragma endregion


private: // メンバ関数


private: // メンバ変数

	// Player
	Player* player_ = nullptr;

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform wt_{};

	// 自機から3Dレティクルへの距離
	const float kDistReticle_ = 10.0f;

	// 自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offsetVec_;
};