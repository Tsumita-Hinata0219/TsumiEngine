#pragma once

#include "GameObject.h"


/* Playerクラス */
class Player {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);


private: // メンバ関数

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();


private: // メンバ変数

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_{};

	// 加算速度
	Vector3 velocity_{};

	// 移動量
	Vector3 move_{};
	float moveSpeed_;

	// 移動限界
	const VHInfo vhInfo = { 12.5f, 1.5f, 14.5f, -14.5f };
};

