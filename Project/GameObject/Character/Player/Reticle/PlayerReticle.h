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
	void Update(ViewProjection view);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw3D(ViewProjection view);
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw2D(ViewProjection view);



#pragma region Get

	/// <summary>
	/// ワールドトランスフォームの取得
	/// </summary>
	WorldTransform GetWorldTransform() { return this->wt3D_; }

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	Vector3 GetWorldPosition() { return this->wt3D_.GetWorldPos(); }

#pragma endregion

#pragma region Set

	/// <summary>
	/// Playerの設定
	/// </summary>
	void SetPlayer(Player* player) { this->player_ = player; }
	
	/// <summary>
	/// ペアレントの設定
	/// </summary>
	void SetParent(WorldTransform* parent) { this->wt3D_.parent = parent; }

#pragma endregion


private: // メンバ関数


private: // メンバ変数

	// Player
	Player* player_ = nullptr;

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// スプライト
	std::unique_ptr<Sprite> sprite_ = nullptr;

	// テクスチャハンドル
	uint32_t reticleTexHD_;

	// ワールドトランスフォーム
	WorldTransform wt3D_{};
	WorldTransform wt2D_{};

	// 自機から3Dレティクルへの距離
	const float kDistReticle_ = 60.0f;

	// 自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offsetVec_;

	// レティクルのテクスチャサイズの半分
	Vector2 size_{};

	Vector3 move_{};

	Vector3 velocity_{};

	Vector2 RStick_{};

	Vector2 spritePos_{};
};